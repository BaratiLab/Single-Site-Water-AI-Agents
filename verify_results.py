"""Reproduce c34 NPT density and locked EOS central estimates from saved arrays."""
import json
from pathlib import Path
import sys
import numpy as np

base = Path(sys.argv[1] if len(sys.argv) > 1 else "restored")
v = base / "outputs/cg_water/round6_validation"
ambient = json.loads((v / "ambient/REPORT.json").read_text())
with np.load(v / "ambient/trajectory.npz") as z:
    density = np.mean(512 * 18.01528 / (0.602214076 * z["volume_A3"]))
np.testing.assert_allclose(density, ambient["density"]["mean"], rtol=1e-8)
X, p = [], []
for j in range(5):
    state = json.loads((v / f"eos/state{j}_REPORT.json").read_text())
    with np.load(v / f"eos/state{j}.npz") as z:
        X.append([1, state["rho"] - 0.99705, z["temperature_K"].mean() - 298.15])
        p.append(z["pressure_bar"].mean())
p0, b, c = np.linalg.lstsq(X, p, rcond=None)[0]
kappa = 1 / (0.99705 * b)
result = dict(intercept_bar=p0, kappa_bar_inverse=kappa, alpha_K_inverse=c*kappa)
reference = json.loads((v / "eos/REPORT.json").read_text())["EOS"]
for key, value in result.items():
    np.testing.assert_allclose(value, reference[key], rtol=1e-8)
print(json.dumps({"density_g_cm3": density, **result}, indent=2))
