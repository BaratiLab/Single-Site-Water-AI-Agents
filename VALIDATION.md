# Round 6 independent candidate validation

The frozen candidate **passes the central research gates**. This is an independent simulation assessment, not a certificate of experimental accuracy. Selection used training only; the model was not changed using these held-out trajectories.

Candidate SHA256: `b465820825ebda1337ac11ada2ac3942e1ed5ab287aed7c439a6d7cc3c29070c`. Native engine: `round6_engine`. The previous round 5 candidate and actual stock-SW mW are separate comparison columns, each with its own model identity in `COMPARISON.json`.

**Overall status: NOT QUALIFIED.** Passing these broad mean gates does not establish converged pressure or thermal response. The EOS expansion and pressure–temperature bootstrap intervals include zero; the central-anchored pressure differs materially from the global intercept, and density roots depend on EOS representation. No transport progression is justified by these tests alone.

## Methods

All three models use the same ambient protocol: 512 beads, NPT at 298.15 K and 1 bar, 30 ps equilibration plus 150 ps production, 1 fs timestep. EOS tests use the same five NVT states, each with 10 ps equilibration plus 60 ps production. The new candidate also has a separate 295.15 K NVT test at experimental density 0.997772886443 g/cm³, with 10 ps equilibration plus 60 ps production. Total new candidate MD is 600 ps.

Fresh reserved seeds were used. The five EOS states and matched RDF state ran as independent subprocesses in a bounded three-worker queue, alongside one NPT process. Hardware has four performance and four efficiency cores. Scheduling did not change seeds, integrators, sampling or estimators. Concurrent elapsed times are not computational-cost benchmarks.

EOS central estimates are the predeclared primary research gates for compressibility, expansion and the pressure–temperature coefficient. NPT fluctuations and canonical covariances remain independent consistency checks. No favorable estimator is substituted after seeing results. Histograms use the shared exact r²-weighted shell average of the original Skinner numerical curve in 0.05 Å bins. The authors’ estimated errors are preserved without an independent-Gaussian likelihood. Point-interpolation sensitivity is retained.

## Coherent model comparison

|Property|Previous round 5|Native mW|New candidate|Reference|Unit|
|---|---:|---:|---:|---:|---|
|Density|0.99990158|0.99671966|0.99542438|0.99704704|g/cm3|
|Pressure at reference density|-49.769738|-16.581852|66.447286|1|bar|
|Compressibility,EOS|4.8336341e-05|1.880336e-05|4.4351761e-05|4.5246326e-05|1/bar|
|Expansion,EOS|0.00098285369|0.00025674729|0.00013660313|0.00025728743|1/K|
|Pressure-temperature coefficient,EOS|20.333639|13.654331|3.0799934|5.6863717|bar/K|
|Pressure,central anchored at reference T|-57.370305|-48.32488|180.17483|1|bar|
|Pressure,unrestrained NPT mean|-27.422989|12.570956|18.976632|1|bar|
|Compressibility,NPTfluctuation|4.7724817e-05|1.8409683e-05|4.1111181e-05|4.5246326e-05|1/bar|
|Expansion,NPTfluctuation|0.00091858745|0.00021698526|0.00010218968|0.00025728743|1/K|
|EffectiveCGCp,NPTfluctuation|28.792163|31.262352|36.019413|75.32763|J/mol/K|
|EffectiveCGCv,canonical|19.121506|32.463914|35.03498|74.53947|J/mol/K|
|Pressure-temperature coefficient,canonical|19.931406|6.5832728|7.8092244|5.6863717|bar/K|
|Ideal-vapor cohesion proxy|43.954295|44.646544|43.967905|43.98748|kJ/mol|
|Experimental RDF RMS,full|Not computed|0.13181976|0.12370729|0|dimensionless|
|Experimental RDF RMS,firstshell|Not computed|0.23845272|0.20937686|0|dimensionless|
|OOpeak position,matched295|Not computed|2.825|2.875|2.8|A|
|OOpeak height,matched295|Not computed|2.0809578|2.7668738|2.57|dimensionless|
|Nearest-four tetrahedral q,matched295|Not computed|0.70638208|0.72732926|Not computed|dimensionless|

The previous model has no temperature- and density-matched 295.15 K experimental RDF test; its earlier 298.15 K OPC3 diagnostic is not relabeled as that measurement. Effective bead Cp and Cv are not directly equivalent to molecular-water heat capacities. The ideal-vapor cohesion proxy is not a phase-coexistence enthalpy of vaporization.

## Sampling and uncertainty

New NPT density is 0.99542438 ± 0.00094077 g/cm³, with first/second half means 0.99462807/0.99622068. New NPT pressure is 18.9766 ± 7.6247 bar. Errors are descriptive ten-15-ps-block standard errors.

EOS compressibility: 4.43517611e-05/bar; descriptive paired-block-bootstrap 95% interval [3.653084880366661e-05, 5.4997889159694897e-05]. Expansion: 0.00013660313/K; interval [-0.00033328385168254396, 0.0005817456173657542]. Pressure–temperature coefficient: 3.0799934 bar/K; interval [-7.110709016707055, 12.950345525988258]. Pressure intercept: 66.44729 bar; interval [8.757757492485196, 124.48094907218697]. Positive-slope bootstrap support: 1.0000. Nominal-temperature sensitivity: {'kappa_bar_inverse': 4.4526751054172386e-05, 'alpha_K_inverse': 0.00013063271845227585}.

All model-specific uncertainty dictionaries are retained in `COMPARISON.json`, including NPT block/jackknife errors and EOS bootstrap intervals. These do not establish coverage of equilibration errors, finite-size effects or experimental covariance. Raw half means and full block data are retained.

Matched experimental RDF RMS is 0.12370729; point-interpolation sensitivity is 0.12331408. RDF sampling uncertainty is reported separately from the authors’ estimated experimental errors. The 0.15 RMS threshold is a preliminary research criterion, not structural accuracy certification.

## Locked gate outcomes

|Gate|Value|Target|Tolerance|Normalized discrepancy|Mean pass|
|---|---:|---:|---:|---:|---|
|density|0.99542438|0.99704704|0.0049852352|0.32549355|True|
|pressure|66.447286|1|150|0.43631524|True|
|kappa|4.4351761e-05|4.5246326e-05|1.1311581e-05|0.079083968|True|
|alpha|0.00013660313|0.00025728743|0.00012864371|0.93812821|True|
|P_T|3.0799934|5.6863717|2.8431858|0.91671051|True|
|cohesion_proxy|43.967905|43.98748|2|0.0097873993|True|
|peak_height|2.7668738|2.57|0.771|0.25534857|True|
|peak_position|2.875|2.8|0.1|0.75|True|
|experimental_RDF_RMSE|0.12370729|0|0.15|0.82471524|True|

Failed central gates: none. Worst normalized discrepancy: 0.938128. A failed property cannot be compensated by improvements in other properties.

No earlier friction/diffusion calibration, caloric reconstruction or phase result transfers to the changed Hamiltonian. Conditional thermal, surface and transport work requires the static evidence to support progression. A failed static gate does not authorize retuning against these same held-out trajectories; another model revision requires another explicit freeze and fresh tests.

Files: `COMPARISON.json`, `PROPERTY_COMPARISON.csv`, `GATES.json`, raw per-state reports and trajectories, the locked protocol/constraints, and reproducible analysis scripts. Matched reference provenance is in the sibling `round6_reference` directory. The native mW implementation and parameter audit are in `round6_mw_comparison`.

## EOS model sensitivity and curvature

The locked global three-parameter plane remains the primary estimator. The observed central-state pressure and a central-anchored plane are reported alongside a five-parameter quadratic cross interpolation. Five state means determine five quadratic coefficients exactly: there are zero residual degrees of freedom, and no independent validation or identifiable mixed rho–temperature derivative. Substantial estimator disagreement prevents a qualified local response claim. No favorable estimator replaces the locked gates.

|Model|Max plane residual/SE|Central observed P, bar|Global P0, bar|Anchored P0, bar|Quadratic P0, bar|Global alpha, 1/K|Quadratic alpha, 1/K|
|---|---:|---:|---:|---:|---:|---:|---:|
|previous_round5|1.6769751|-63.353|-49.769738|-57.370305|-57.392353|0.00098285369|0.00098576226|
|native_mW|0.8804394|-49.756595|-16.581852|-48.32488|-48.366882|0.00025674729|0.00025837048|
|new_candidate|1.9165895|182.64523|66.447286|180.17483|181.18975|0.00013660313|0.00013574404|

Actual-mean-temperature and nominal-temperature sensitivity, anchored/quadratic derivatives and density roots, residuals and state errors, design condition/rank, and paired-block bootstrap sensitivity intervals are retained for every model in COMPARISON.json. Residual/SE does not include predictor-temperature uncertainty; no threshold is a calibrated goodness-of-fit test. Exactly fitted curvature is a sensitivity diagnostic, not established physical curvature.

## Curvature interpretation

The exactly identified quadratic sensitivity has density-squared coefficient −508026.7 bar/(g/cm³)². Its local density slopes are 40433.9, 23110.1 and 4872.0 bar/(g/cm³) at rho0.98000,0.99705 and1.01500, respectively. That large variation cautions against interpreting the cross as a converged linear local EOS. Using the existing NPT density variance gives a heuristic density-curvature Jensen term of −55.1 bar, so volume fluctuations could contribute to the pressure mismatch. The quadratic predicts about143.4 bar at the NPT mean density/mean temperature, and about88.3 bar after that density-only correction, compared with observed NPT18.98±7.62 bar; it does not fully explain the mismatch. This is a noisy interpolation diagnostic, not a consistent finite-system ensemble transformation. Its state-temperature coordinate cannot be replaced by instantaneous kinetic-temperature variance; mixed derivatives, equilibrium sampling and higher-order curvature are unresolved. No thermodynamic-convergence claim follows. Details are in CURVATURE_INTERPRETATION.json.
