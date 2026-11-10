# Round 6: frozen joint water-potential calibration

Primary candidate **c34 is frozen for fresh validation**. It passes all eight fitted research gates by the training means. This is not an independently qualified water model: density has only been predicted from the training EOS, thermal uncertainty remains large, and transport, dielectric response, calorimetry and phase equilibria have not been validated for this candidate.

The model is a neutral, one-bead mechanical water potential. It combines a refitted radial cubic spline, a compact coordination descriptor with stabilized quartic embedding, a sparse lower-coordination correction and a tetrahedral angular invariant. The selected angular strength is constant; the independent density-angular functions were searched but do not survive in this primary model. Its polynomial angular radial weight is degree14 in Q, evaluated as t³Q(t)². This is a polynomial representation of invariant scalar functions, not a single global Cartesian polynomial.

## Frozen primary training results

|Observable|Reference|c34 training mean|Comparison|
|---|---:|---:|---|
|Pressure / bar|1|69.29037|+68.29 bar|
|Compressibility / bar⁻¹|4.5246326e-05|5.6252461e-05|+24.32%|
|Thermal expansion / K⁻¹|0.00025728743|0.00029137492|+13.25%|
|Thermal pressure derivative / bar K⁻¹|5.6863717|5.1797719|-8.91%|
|Cohesion proxy / kJ mol⁻¹|43.98748|44.074541|+0.20%|
|First peak height|2.57|2.7828789|+8.28%|
|First peak position / Å|2.8|2.825|+0.89%|
|Experimental RDF RMSE|0|0.1249041|research gate ≤0.15|

EOS reference:298.15 K and rho0=0.997047039 g/cm³. The five-state fit uses measured mean temperatures, not thermostat targets. The cohesive quantity is the monatomic-CG isolated-minus-liquid potential-energy proxy plus RT; it is not a vapor–liquid coexistence calculation.

The RDF reference is the original Skinner2013 numerical oxygen–oxygen curve at295.15 K. Exact r² shell averages are compared with0.05 Å simulation bins over2.4–5.8 Å. Published point-peak height2.57 and binned reference peak~2.538 are different estimators; the declared30% peak gate uses2.57. The RDF trajectory thermostat was295.15 K and its actual mean was 295.234 K.

The diagnostic five-block bootstrap ranges are broad: kappa4.44–7.88×10⁻⁵/bar, alpha−0.31–7.60×10⁻⁴/K and P_T−0.51–12.22 bar/K. Five6 ps blocks can underestimate slow correlations. These ranges do not establish converged accuracy or confidence-qualified feasibility.

## Selection and density

The strict original minmax winner was **c33**, score0.93529. Primary c34 has score0.97300. An explicit **PRE-HOLDOUT selection amendment** chose c34 for lower predicted density risk among the two same-budget mean-feasible, near-tied candidates. It is incorrect to say that the original strict minmax rule selected c34. c33 remains byte-exact in strict_minimax_candidate.json. See SELECTION_AMENDMENT.json for timing, training snapshot hash and the rule.

The global linear-EOS root predictsc34 density0.993217 g/cm³ (−0.384%); a central-pressure-anchored prediction gives0.993647 g/cm³ (−0.341%). Their diagnostic bootstrap intervals are0.988627–0.997164 and0.986527–1.000654 g/cm³. These are model predictions, not measured NPT density success. c33 predictions were+0.699% and+0.568%, outside the intended0.5% density tolerance.

Linear-plane pressure can disagree with the directly sampled central pressure when the EOS curves. For c34, plane P0=69.29 bar, central T-corrected pressure61.63 bar, and a saturated five-parameter quadratic-axis diagnostic gives P0=61.70 bar, kappa5.6245×10⁻⁵/bar and alpha2.9707×10⁻⁴/K. The quadratic fit has five parameters for five means and is a sensitivity diagnostic, not an additional validation or a replacement ranking. c32 had a much larger plane/central disagreement; that failure is preserved.

Fresh NPT, EOS and matched-temperature RDF runs must test the frozen PRIMARYc34. A failed fresh test must be reported; the primary must not be retrospectively swapped to c33 using heldout outcomes.

## Same-budget larger-cell training comparisons

|Candidate|Worst normalized discrepancy|P / bar|kappa / bar⁻¹|alpha / K⁻¹|P_T / bar K⁻¹|RDF RMSE|
|---|---:|---:|---:|---:|---:|---:|
|r6_N512_c33|0.9353|-139.29|4.983376e-05|0.00021678|4.350|0.1270|
|r6_N512_c34|0.9730|69.29|5.625246e-05|0.0002913749|5.180|0.1249|
|r6_N512_c32|1.8053|92.33|6.566715e-05|0.0001655987|2.522|0.1253|
|r6_N512_c16|1.8226|120.23|2.462992e-05|0.0001182918|4.803|0.1210|
|r6_N512_c30|2.0522|308.83|3.234577e-05|0.0001162952|3.595|0.1284|
|r6_N512_c28|2.0563|50.28|2.198583e-05|5.362962e-05|2.439|0.1288|
|r6_N512_c23|2.2449|74.28|1.985253e-05|0.0001282395|6.460|0.1181|
|r6_N512_c31|8.8580|40.66|0.0001454442|0.0003941494|2.710|0.1213|

## Search, actual MD and lessons

There were32 actual five-state N64 screens, eight same-budget six-state N512 refinements and35 unique candidate models. N64 screens used5 ps equilibration plus20 ps production per state. N512 refinements used10 ps equilibration plus30 ps production per state, with a separate295.15 K RDF state. Integration timestep was1 fs; static-property trajectories used Langevin gamma5 ps⁻¹. This thermostat does not validate diffusion or a physical CG clock.

The native upstream LLM-SR Sampler/Evaluator/ExperienceBuffer registered actual MD training fitness. Seven intermediate prompts and evaluation logs were read before adaptive proposals. The finite agent-authored grammar search used no external LLM API and does not prove a global symbolic optimum. The mW-like seed is a literature-informed polynomial approximation, not an ab-initio force-trained discovery. Original c21 and polynomial-mW controls are preserved.

The failed canonical Born/variance compressibility estimator differed~68% from an available training EOS check and was excluded from all candidate fitness. Actual finite-difference EOS replaced it. Initial static proposals also exposed poor ensemble overlap when c21 frames were used for the mW family; later proposals used matching-parent frames.

Pair-well cohesion compensation stiffened the liquid. A sparse lower-coordination quartic, with nstar=.50 chosen from the training lower tail, instead adjusts isolated-bead energy while barely acting in bulk liquid. This is not vapor-pressure or interface validation. Broader coordination support 5.5 Å produced a stronger compressibility response than the first-shell descriptor. Negative quadratic embedding is always stabilized by positive quartic embedding.

Large radial coordinate warps failed pressure/RDF or EOS stability and were rejected. A manifest positional-lookup bug caused four repeated-parent EOS runs; it was caught before warped-trial registration, preserved under diagnostic_wrong_spec_lookup, excluded from selection and corrected by explicit candidate identity lookup. All40 selected-search records now pass model-path and SHA256 audit.

The exact retained budget is **7.04 ns of actual integration**, including failed/excluded diagnostics:5.00 ns N64 and2.04 ns N512,7,040,000 steps across250 complete trajectories. Aggregate reported LAMMPS loop time is2376.3s, accumulated across concurrent training. That is not exclusive benchmark time or OS CPU time and must not be used as a performance comparison.

## Remaining scientific limits

Positive ambient EOS slope, positive quartic stabilization and benign short-run density diagnostics are not proofs of phase stability or transferability. Freezing, boiling, vapor pressure, interfaces, cavities, high pressure, supercooling and isotope effects remain untested. The sparse low-coordination term especially requires gas-cluster and evaporation/coexistence checks. A neutral bead has no molecular dipole; dielectric response requires additional observables and field-consistent physics. Caloric internal degrees of freedom and a validated physical dynamics clock are absent.

Existing legacy metadata inside the frozen JSON records historical round3/round5 initialization. It does not describe the current fit or establish current property validation. FREEZE.json, this report, TRAINING_SELECTION.json and SELECTION_AMENDMENT.json provide current provenance. The selected JSON remains byte-exact.

## Artifacts

- selected_candidate.json and FREEZE.json: frozen primary and hash.
- SYMBOLIC_MODEL.md and selected_radial_coefficients.csv: exact symbolic descriptors and radial coefficients.
- TRIALS.json, IDENTITY_HASH_AUDIT.json and RUN_BUDGET.json: measured training records and audit.
- TRAINING_PROGRESS.png/pdf: bounded search, EOS tradeoffs and matched RDF curves.
- STABILITY_DIAGNOSTICS.json: finite-box minimum-distance, coordination and small-wavevector checks.
- NEXT_TERMS.txt: training-only lessons for future work, not additional fitting this round.

Frozen SHA256: `b465820825ebda1337ac11ada2ac3942e1ed5ab287aed7c439a6d7cc3c29070c`.
