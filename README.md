# CMS Open Data: Invariant Mass Reconstruction ($H \to ZZ^* \to 4\mu$)

A lightweight high-energy physics pipeline to stream, process, and reconstruct the invariant mass spectrum of the Higgs Boson ($H \to ZZ^* \to 4\mu$) using official CMS Open Data from CERN via the XRootD streaming protocol.

> 📖 **Physics Documentation:** For a detailed breakdown of the Higgs mechanism, $H \to ZZ^* \to 4\mu$ decay dynamics, and relativistic kinematics, see [PHYSICS.md](PHYSICS.md).

---

## Dataflow Architecture

The analysis bypasses the need for local multi-gigabyte dataset downloads by streaming raw collision trees directly from CERN EOS storage clusters in Geneva.

```text
[1. CERN EOS Storage Cluster (Geneva)]
          │ (XRootD Streaming of pt, eta, phi per muon)
          ▼
[2. Kinematic Conversion & Event Loop]
          │ ──> Convert (pt, eta, phi, m) → (E, px, py, pz) for 4 muons
          │ ──> Sum four-momenta vectors across particles
          │ ──> Compute invariant mass: m = sqrt(E^2 - p^2)
          ▼
[3. Statistical Reconstruction & Plotting]
          │ ──> Histogram binning (70 - 150 GeV)
          └─> Signal Peak Emergence at 125 GeV (Higgs Resonance)
```
## 📁 Repository Structure

* [include/](./include/) — Directory containing header files
  * [include/Particle.hpp](./include/Particle.hpp) — Particle kinematics and Lorentz vector structures
* [src/](./src/) — Source code directory
  * [src/main.cpp](./src/main.cpp) — Processing loop & invariant mass reconstruction
* [CMakeLists.txt](./CMakeLists.txt) — Cross-platform CMake build configuration
* [PHYSICS.md](./PHYSICS.md) — Theoretical derivations and physics background
* [cms_event_display.png](./cms_event_display.png) — CMS event display visualization
* [LICENSE](./LICENSE) — MIT License
* [README.md](./README.md) — Project documentation and setup guide

🛠️ Build & Running

This project uses CMake for build automation and cross-platform compilation.

    Prerequisites

    C++ Compiler with C++17 support (g++ or clang++)
    Build System: cmake (v3.12 or higher)

    Compilation Steps

   1. Clone the repository:
    Bash

    git clone https://github.com/smegmusss/CMS-Higgs-reconstruction.git
    cd CMS-Higgs-reconstruction

   2. Generate Makefiles and compile:
    Bash

    mkdir -p build && cd build && cmake .. && make

   3. Execute the binary:
    Bash

    ./higgs_recon

