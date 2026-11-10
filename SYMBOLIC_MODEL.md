# Frozen symbolic potential

The selected nonzero expression is

U = sum_pairs phi(r) + sum_i [ -0.166793155920783 d_i −2.8 d_i² +0.2 d_i⁴ +5.99956483923027 max(0,1−2n_i)⁴ +599.4640644 A_i ],

d_i=n_i−2.53691943794851, n_i=sum_j max(0,1−r_ij²/5.5²)³.
All scalar energy coefficients are kJ/mol. The angular invariant below uses cutoff 4.3065 Å and the recorded degree14 Q. The exact pair cubic has a physical cutoff 4.3065 Å; appended zero intervals extend only the neighbor representation to6 Å.

U = sum_(i<j) phi(rij) + sum_i [K1*d_i + K2*d_i² + h3*d_i³ + h4*d_i⁴ + A3*s_i³ + A4*s_i⁴ + L(n_i)*A_i].

d_i=n_i−n0; n_i=sum_j max(0,1−rij²/rd²)³; s_i=max(0,1−n_i/nstar).
L(n)=l0+l1*(n−nref)+l2*(n−nref)² when angular_polynomial exists; otherwise inherited square fallback.
Angular w(r)=t³ Q(t)², t=max(0,1−r²/rc²), Q(t)=sum_k q_k*t^k.
A_i=sum_(j<k) w(rij)*w(rik)*(cos(theta_jik)+1/3)².
The engine evaluates this invariant with vector and tensor moments, not explicit neighbor-triplet enumeration.
phi(r)=c3_j*(r−a_j)³+c2_j*(r−a_j)²+c1_j*(r−a_j)+c0_j on each interval [a_j,a_(j+1)); exact coefficients in selected_radial_coefficients.csv. Below first knot, phi=phi(a0)+phi'(a0)*(r−a0)+10000*(r−a0)^4; above final knot, zero.

All coefficients below are exact frozen JSON values; energies kJ/mol, distances Angstrom, dimensionless coordination. These are per-bead many-body functions, not water charges or a dielectric model.

```json
{
  "embedding": {
    "K2": -2.8,
    "K1": -0.1667931559207833,
    "n0": 2.536919437948505,
    "rd": 5.5,
    "h3": 0.0,
    "h4": 0.2
  },
  "undercoordination": {
    "A3": 0.0,
    "A4": 5.999564839230267,
    "nstar": 0.5
  },
  "angular_polynomial": {
    "l0": 599.4640644,
    "l1": 0,
    "l2": 0,
    "nref": 2.536919437948505
  },
  "angular_cutoff_A": 4.3065,
  "angular_weight": {
    "coefficients_ascending": [
      -0.05584374858176977,
      13.813681810734714,
      -482.4017976897535,
      7165.51424376389,
      -57527.64697894118,
      297172.1111663983,
      -1072499.746376668,
      2814643.0354031,
      -5466093.281733246,
      7873236.650911203,
      -8316283.856326343,
      6264895.24457229,
      -3188503.053282442,
      982889.721893812,
      -138626.9692042507
    ]
  }
}
```
