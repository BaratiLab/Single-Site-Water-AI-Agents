# Single Site Water AI Agents

Research companion to [Agentic Swarm Discovery of Single-Site Water Molecule](https://www.overleaf.com/project/6aefaeab03ca6c90d78d75b2). One neutral bead represents each water molecule. The frozen c34 Hamiltonian combines a radial cubic spline, tetrahedral angular moments, and coordination corrections.

| Fresh result | c34 | Native mW | Water reference |
|---|---:|---:|---:|
| Density (g/cm³) | 0.99542 ± 0.00094 | 0.99672 | 0.99705 |
| EOS compressibility (10⁻⁵/bar) | 4.435 | 1.880 | 4.525 |
| EOS expansion (10⁻⁴/K) | 1.366 | 2.567 | 2.573 |
| Experimental RDF RMS | 0.12371 | 0.13182 | — |

The campaign examined 35 distinct parameter sets and used 7.04 ns of training integration. Candidate c34 was frozen before 600 ps of fresh validation. The original strict training minimax winner was c33; a disclosed pre-holdout density-risk amendment selected c34. The pressure plane gives 66.45 bar, versus 182.65 bar from the directly sampled central state. Thermal-response intervals include zero. **The model remains unqualified for general-purpose water simulation.** No c34 diffusion or phase result is claimed. The fused implementation averaged 8.29 s/10 ps versus 7.59 s for native mW in its matched timing series; this does not establish a speed advantage.

- [Manuscript](Manuscript.pdf), [supplement](Supplement.pdf), and [editable Overleaf archive](Overleaf-project.zip).
- [Full results](RESULTS.txt), [training](TRAINING.md), [validation](VALIDATION.md), [property CSV](PROPERTY_COMPARISON.csv), and [symbolic model](SYMBOLIC_MODEL.md).
- [Frozen parameter JSON](frozen-c34.json), [radial coefficients](radial_coefficients.csv), and native LAMMPS source, initial coordinates, parameters, and input at repository root.
- [Campaign source and audit](Campaign-source-and-audit.zip) preserves the scripts, figures, audits, and vendored LLM-SR. The numbered Campaign-data ZIPs contain the round-six saved trajectories, logs, simulation inputs, and supporting historical inputs. [DATA_MANIFEST.json](DATA_MANIFEST.json) lists their hashes. The large earlier three-site initialization trajectory is represented by the exact final frame and cell read by the round-six scripts.

## Reproduce

Run `python restore_campaign.py restored` with Python 3.9+ to check and extract the source and all numbered data archives into their historical relative layout. Use `restored/outputs/cg_water/round6_summary/README.txt` as the campaign index. Historical absolute paths in scripts and reports may require relocation; preserve originals when auditing hashes. Restoration checks archive integrity, not scientific convergence.

Run `python -m pip install numpy`, then `python verify_results.py restored` to reproduce the c34 density and the five-state EOS central estimates directly from archived arrays. The complete RDF, uncertainty, training, and timing scripts are in the restored campaign tree; archived wall times are hardware-specific.

For a fresh LAMMPS smoke run, build with `python build_portable.py` against a matching plugin-enabled LAMMPS Python installation with C++17 headers and shared library. Use a compatible serial LAMMPS executable (or its Python interface) with:

```sh
lmp -in example_nvt.in.template -var PLUGIN /absolute/path/to/cg_joint_rebuilt.dylib -var START_DATA frozen_start512.data -var MODEL_PARAMS frozen_model.params
```

Use the .so suffix on Linux. This is a 10 ps NVT mechanics example. See [the campaign reproduction notes](CAMPAIGN_REPRODUCTION.txt) for the scope, build details and diagnostics. The engine is serial and orthogonal only; the run does not certify equilibrium, diffusion, or transferability. The LAMMPS-linked source retains its GPL notices. Third-party materials retain their own terms.
