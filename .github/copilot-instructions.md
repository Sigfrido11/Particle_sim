# Guidance for AI coding agents

Purpose: help an AI quickly become productive in this Monte Carlo particle-simulation repo.

- **Quick build & run**:
  - Configure and build with CMake: `cmake -S . -B build && cmake --build build -j`
  - Run generator: `./build/particle_sim` (creates `histo.root`).
  - Run analysis in ROOT: `root -l -q analised.cpp` or in an interactive ROOT session: `.x analised.cpp`.

- **Key files & responsibilities**:
  - `main.cpp`: event generator and histogram definitions (particle types are registered via `Particle::AddParticleType`).
  - `particle.cpp` / `particletype.cpp` / `resonancetype.cpp`: physics core (energy, invariant mass, `Decay2Body`, width handling, boosting).
  - `analised.cpp`: analysis checks, histogram subtraction (opposite - same charge) and fitting (Gaussian, expo), writes PDFs/ROOT outputs.
  - `CMakeLists.txt`: depends on ROOT; use `-DROOT_DIR` if CMake cannot find ROOT automatically.

- **Project-specific conventions** (important for edits and tests):
  - Particle type names are string keys (exact match): they are defined in `main.cpp` and compared by name when filling specialized histograms — do not refactor these strings without updating both producer and analyzer.
  - Histogram names are literal identifiers in `main.cpp` and used by `analised.cpp` (`gen_particles`, `azimuth`, `p_module`, `dec_inv_mass`, `pi_k_opposite`, etc.). Changing a name in one file requires updating the other.
  - Units: mass/energy/momentum are in GeV (see particle masses in `main.cpp`).
  - Random seeds: `gRandom->SetSeed(200769)` in `main.cpp` controls deterministic runs for tests.
  - Decay/return codes: `Particle::Decay2Body` returns 0 on success, 1 if mass==0, 2 if mass too low — use these to guard modifications.

- **Testing & validation patterns**:
  - `analised.cpp` implements many sanity checks based on the generator settings (expected fractions, entry count ranges, and fit parameter checks). When editing generator parameters (event counts, probabilities), update these thresholds accordingly.
  - Signal extraction pattern: construct `difference = opposite_charge - same_charge` and `difference_pi_k = pi_k_opposite - pi_k_same` before fitting.

- **Common tasks and examples**:
  - To change particle fractions, edit selection thresholds in `main.cpp` where `type = gRandom->Rndm()` is compared to numeric cutoffs.
  - To add a new resonance type, call `Particle::AddParticleType("name", mass, charge, width)` in `main.cpp` and ensure `analised.cpp` accounts for its decay products.
  - To change histogram binning or ranges, update both the creation in `main.cpp` and any axis/title code in `analised.cpp` that assumes ranges.

- **Build/CI notes for maintainers**:
  - ROOT is an external dependency. Ensure `root-config` is on `PATH` or set `-DROOT_DIR` when invoking CMake.
  - The produced binary is `build/particle_sim` (not `particle`), and `histo.root` is generated in the working directory.

If anything here is unclear or you'd like the instructions expanded with examples (e.g., where to change particle probabilities or how to run a debug build), tell me which section to expand.
