"""Build into a NEW artifact; never overwrite a live loaded plugin. GPL-2.0-or-later."""
from pathlib import Path
import argparse,subprocess,shutil,sys
import lammps
H=Path(__file__).resolve().parent;L=Path(lammps.__file__).resolve().parent
p=argparse.ArgumentParser();p.add_argument('--output',type=Path,default=H/('cg_joint_rebuilt.dylib' if sys.platform=='darwin' else 'cg_joint_rebuilt.so'));a=p.parse_args()
compiler=shutil.which('clang++') or shutil.which('g++')
if not compiler:raise RuntimeError('C++17 compiler required')
if not (L/'include/lammps/pair.h').exists():raise RuntimeError('Installed matching LAMMPS development headers required')
cmd=[compiler,'-O3','-std=c++17','-fPIC','-shared',f'-I{L}/include/lammps',f'-I{L.parent}/include',f'-I{H}',str(H/'cg_moment.cpp'),f'-L{L}','-llammps',f'-Wl,-rpath,{L}','-o',str(a.output)]
subprocess.run(cmd,check=True);print(a.output)
