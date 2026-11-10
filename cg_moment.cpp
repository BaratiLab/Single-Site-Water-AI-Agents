// GPL-2.0-or-later. Serial research LAMMPS plugin; full angular model, full-neighbor exact moments.
#include "pair.h"
#include "neighbor.h"
#include "neigh_list.h"
#include "atom.h"
#include "memory.h"
#include "error.h"
#include "domain.h"
#include "comm.h"
#include "update.h"
#include "lammps.h"
#include "lammpsplugin.h"
#include <vector>
#include <fstream>
#include <cmath>
#include <cstring>
using namespace LAMMPS_NS;
class CGJoint final:public Pair {
 std::vector<double> k,c,q={1.};double lam,rc,K2=0,K1=0,n0=0,rd=5,A3=0,A4=0,nstar=1,bcoord=0,nref=0,l0=0,l1=0,l2=0,nrefpoly=0,h3=0,h4=0;int angular_poly=0;
 struct Edge {int j;double r,u[3],w,dw;};std::vector<Edge> edges;
 void radial(double r,double &v,double &dv){if(r>=k.back()){v=dv=0;return;}if(r<k[0]){double z=r-k[0];v=c[3]+c[2]*z+1e4*pow(z,4);dv=c[2]+4e4*pow(z,3);return;}int b=0;while(b<(int)k.size()-2&&r>k[b+1])b++;double z=r-k[b];double *a=&c[4*b];v=((a[0]*z+a[1])*z+a[2])*z+a[3];dv=(3*a[0]*z+2*a[1])*z+a[2];}
 void wvir(const double*d,const double*g,double factor){if(vflag_global){virial[0]-=factor*d[0]*g[0];virial[1]-=factor*d[1]*g[1];virial[2]-=factor*d[2]*g[2];virial[3]-=factor*d[0]*g[1];virial[4]-=factor*d[0]*g[2];virial[5]-=factor*d[1]*g[2];}}
 public:
 CGJoint(LAMMPS*l):Pair(l){single_enable=0;restartinfo=0;manybody_flag=1;one_coeff=1;no_virial_fdotr_compute=1;}
 ~CGJoint()override{if(allocated){memory->destroy(setflag);memory->destroy(cutsq);}}
 void settings(int n,char**)override{if(n)error->all(FLERR,"No style arguments");}
 void coeff(int n,char**arg)override{if(n!=3)error->all(FLERR,"Expected * * params");std::ifstream f(arg[2]);int m;f>>m>>lam>>rc;k.resize(m);c.resize(4*(m-1));for(double &v:k)f>>v;for(double &v:c)f>>v;if(!f)error->all(FLERR,"Bad CG params");f>>K2>>K1>>n0>>rd;if(!f){K2=K1=n0=0;rd=rc;}f.clear();if(!(f>>A3>>A4>>nstar>>bcoord>>nref)){A3=A4=bcoord=nref=0;nstar=1;}f.clear();int qdegree;if(f>>qdegree){if(qdegree<0||qdegree>16)error->all(FLERR,"Angular weight degree outside0to16");q.resize(qdegree+1);for(double &v:q)f>>v;if(!f)error->all(FLERR,"Bad angular polynomial coefficients");}else{q.assign(1,1.);}f.clear();if(!(f>>angular_poly>>l0>>l1>>l2>>nrefpoly>>h3>>h4)){angular_poly=0;h3=h4=0;}
 if(angular_poly&&(l0<=0||l2<0||(l2==0&&l1!=0)||(l2>0&&l1*l1>=4*l0*l2)))error->all(FLERR,"Angular polynomial must be strictly positive for all coordination");if(h4<0||(h3!=0&&h4<=0))error->all(FLERR,"Cubic embedding requires positive quartic stabilization");if(K2<0&&h4<=0)error->all(FLERR,"Negative quadratic embedding requires positive quartic stabilization");if(nstar<=0||A3<0||A3+2*A4<0||lam<0)error->all(FLERR,"Invalid nonconvex undercoordination or angular parameters");if(rd<=0)error->all(FLERR,"Nonpositive embedding cutoff");if(rd>k.back())error->all(FLERR,"Embedding cutoff exceeds pair cutoff");if(!allocated){allocated=1;memory->create(setflag,2,2,"cg:setflag");memory->create(cutsq,2,2,"cg:cutsq");}setflag[1][1]=1;}
 void init_style()override{if(comm->nprocs!=1||domain->triclinic||strcmp(update->unit_style,"real"))error->all(FLERR,"CG benchmark requires serial orthogonal real units");neighbor->add_request(this,NeighConst::REQ_FULL);if(2*k.back()>=fmin(domain->xprd,fmin(domain->yprd,domain->zprd)))error->all(FLERR,"Box too small");}
 double init_one(int,int)override{return k.back();}
 void compute(int ef,int vf)override{ev_init(ef,vf);int n=atom->nlocal;double **x=atom->x,**F=atom->f;
 for(int ii=0;ii<list->inum;ii++){int i=list->ilist[ii];edges.clear();double nn=0,p[3]={},Q[3][3]={},w2=0;
 for(int jj=0;jj<list->numneigh[i];jj++){int j=list->firstneigh[i][jj]&NEIGHMASK;double d[3];for(int a=0;a<3;a++)d[a]=x[j][a]-x[i][a];double r=sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2]);if(r>=k.back())continue;if(r<1e-10)error->one(FLERR,"Coincident CG beads");double v,dv;radial(r,v,dv);if(eflag_global)eng_vdwl+=.5*v/4.184;double g[3];for(int a=0;a<3;a++){g[a]=dv*d[a]/r/4.184;F[i][a]+=g[a];}wvir(d,g,.5);
 if(r>=rc)continue;Edge e;e.j=atom->map(atom->tag[j]);e.r=r;double s=1-r*r/(rc*rc);if(q.size()==1&&q[0]==1.){e.w=s*s*s;e.dw=-6*r/(rc*rc)*s*s;}else{double Q=q.back(),Qp=0.;for(int qi=(int)q.size()-2;qi>=0;qi--){Qp=Qp*s+Q;Q=Q*s+q[qi];}e.w=s*s*s*Q*Q;e.dw=(3*s*s*Q*Q+2*s*s*s*Q*Qp)*(-2*r/(rc*rc));}nn+=e.w;w2+=e.w*e.w;for(int a=0;a<3;a++){e.u[a]=d[a]/r;p[a]+=e.w*e.u[a];for(int b=0;b<3;b++)Q[a][b]+=e.w*d[a]*d[b]/(r*r);}edges.push_back(e);}
 double rho=0;
 for(int jj=0;jj<list->numneigh[i];jj++){int j=list->firstneigh[i][jj]&NEIGHMASK;double r2=0;for(int a=0;a<3;a++){double d=x[j][a]-x[i][a];r2+=d*d;}if(r2<rd*rd){double s=1-r2/(rd*rd);rho+=s*s*s;}}
 double q2=0,p2=0;for(int a=0;a<3;a++){p2+=p[a]*p[a];for(int b=0;b<3;b++)q2+=Q[a][b]*Q[a][b];}
 double Ai=.5*(q2+2*p2/3+nn*nn/9-16*w2/9),sunder=fmax(0.,1-rho/nstar),fac=1+bcoord*(rho-nref),Leff=lam*fac*fac,Lprime=2*lam*bcoord*fac,dn=rho-n0; if(angular_poly){double z=rho-nrefpoly;Leff=l0+l1*z+l2*z*z;Lprime=l1+2*l2*z;}
 double dedn=2*K2*(rho-n0)+K1+3*h3*dn*dn+4*h4*dn*dn*dn-(3*A3*sunder*sunder+4*A4*sunder*sunder*sunder)/nstar+Lprime*Ai;
 if(eflag_global)eng_vdwl+=(K2*(rho-n0)*(rho-n0)+K1*(rho-n0)+A3*pow(sunder,3)+A4*pow(sunder,4)+h3*dn*dn*dn+h4*dn*dn*dn*dn+Leff*Ai)/4.184;
 for(int jj=0;jj<list->numneigh[i];jj++){int j=list->firstneigh[i][jj]&NEIGHMASK;double d[3],r2=0;for(int a=0;a<3;a++){d[a]=x[j][a]-x[i][a];r2+=d[a]*d[a];}if(r2<rd*rd){double s=1-r2/(rd*rd),g[3];int localj=atom->map(atom->tag[j]);for(int a=0;a<3;a++){g[a]=dedn*(-6/(rd*rd))*s*s*d[a]/4.184;F[i][a]+=g[a];F[localj][a]-=g[a];}wvir(d,g,1);}}

 for(auto&e:edges){double qu[3]={},uqu=0,pu=0;for(int a=0;a<3;a++){for(int b=0;b<3;b++)qu[a]+=Q[a][b]*e.u[b];uqu+=e.u[a]*qu[a];pu+=p[a]*e.u[a];}double gw=Leff*(uqu+2*pu/3+nn/9-16*e.w/9),gu[3],dot=0;for(int a=0;a<3;a++){gu[a]=Leff*e.w*(2*qu[a]+2*p[a]/3);dot+=gu[a]*e.u[a];}double g[3],d[3];for(int a=0;a<3;a++){g[a]=(e.dw*gw*e.u[a]+(gu[a]-e.u[a]*dot)/e.r)/4.184;F[i][a]+=g[a];F[e.j][a]-=g[a];d[a]=e.r*e.u[a];}wvir(d,g,1);}
 }
 }
};
static Pair *make(LAMMPS*l){return new CGJoint(l);}extern "C" void lammpsplugin_init(void*l,void*h,void*r){lammpsplugin_t p={};p.version=static_cast<LAMMPS*>(l)->version;p.style="pair";p.name="cg/joint";p.info="Serial full-neighbor exact CG moments";p.author="Research";p.creator.v1=(lammpsplugin_factory1*)&make;p.handle=h;((lammpsplugin_regfunc)r)(&p,l);}
