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

