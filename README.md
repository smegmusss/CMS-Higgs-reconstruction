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

📁 Repository Structure

    * include/Particle.hpp: Header file defining particle kinematics and 4-momentum structure
    * src/main.cpp: Event processing loop & 4-muon invariant mass calculation
    * CMakeLists.txt: Cross-platform CMake build system configuration
    * PHYSICS.md: Theoretical kinematic derivation and physics background
    * cms_event_display.png: Visual representation of a 4-muon event in the CMS detector
    * README.md: Project architecture and execution guide

🛠️ Build & Running

This project uses CMake for build automation and cross-platform compilation.
Prerequisites

    * C++ Compiler with C++17 support (g++ or clang++)
    * Build System: cmake (v3.12 or higher)

Compilation Steps

    1. Clone the repository:
     git clone [https://github.com/smegmusss/CMS-Higgs-reconstruction.git](https://github.com/smegmusss/CMS-Higgs-     reconstruction.git)

    2. Generate Makefiles and compile:
    mkdir -p build && cd build && cmake .. && make

    3. Execute the binary:
    ./higgs_recon
