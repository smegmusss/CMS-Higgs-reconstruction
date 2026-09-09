# Physics Background: $H \to ZZ^* \to 4\mu$ Invariant Mass Reconstruction

This document outlines the theoretical physics, kinematic calculations, and data selection logic behind my reconstruction project for the Higgs Boson using CERN CMS Open Data.

---

## The Higgs Field and Mass Generation

In the Standard Model of particle physics, fundamental particles acquire their rest mass through their interaction with the **Higgs field** via the mechanism of spontaneous electroweak symmetry breaking. 

The **Higgs boson ($H$)** is the scalar quantum excitation of this field. It was discovered in 2012 by the CMS and ATLAS collaborations at CERN with a measured rest mass of:

$$m_H \approx 125.1 \text{ GeV/c}^2$$

Because the Higgs boson has an extremely short lifetime ($\sim 10^{-22}\text{ s}$), it decays almost instantaneously at the collision point (primary vertex). We cannot observe it directly inside the CMS detector; we can only reconstruct its properties by measuring the particles produced in its decay chain.

---

## Decay Dynamics: The $H \to ZZ^* \to 4\mu$ Channel

Among various possible decay modes, this project focuses on the decay into two $Z$ vector bosons, which subsequently decay into two pairs of opposite-charge muons:

$$p + p \longrightarrow H \longrightarrow Z + Z^* \longrightarrow (\mu^+ \mu^-) + (\mu^+ \mu^-)$$

```text
       pp Collision ──> Higgs Boson (H)
                            │
                            ├──> Z Boson (On-shell, real)       ──> μ⁺ + μ⁻
                            └──> Z* Boson (Off-shell, virtual)  ──> μ⁺ + μ⁻
