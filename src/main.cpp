/**
 * @file main.cpp
 * @author smegmusss
 * @brief CMS Higgs to 4 muons invariant mass reconstruction (Explicit Math).
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "../include/Particle.hpp"

using namespace std;

int main() {

    // Simulated input data for the 4 detected muons 
    vector<Particle> muons = {
        Particle(37.5, -0.4,  1.2),
        Particle(31.2,  0.8, -1.9),
        Particle(24.1,  1.1,  2.8),
        Particle(12.8, -1.5, -0.5)
    };

    // Kinematic cut: pt treshold = 5.0
    bool passesCut = true;
    for (const auto& muon : muons) {
        double pt = sqrt(muon.px * muon.px + muon.py * muon.py);
        if (pt < 5.0) {
            passesCut = false;
            break;
        }
    }

    if (!passesCut) {
        cout << "Event rejected: one or more muons failed the pT threshold!" << endl;
        return 0;
    }

    // Sum the 4 momentum components
    double px_tot = 0.0;
    double py_tot = 0.0;
    double pz_tot = 0.0;
    double energy_tot = 0.0;

    for (const auto& muon : muons) {
        px_tot += muon.px;
        py_tot += muon.py;
        pz_tot += muon.pz;
        energy_tot += muon.energy;
    }

    // Calculate the squared total 3D momentum
    double p2_tot = px_tot * px_tot + py_tot * py_tot + pz_tot * pz_tot;

    // Calculate the invariant mass
    double m4mu = 0.0;
    if (energy_tot * energy_tot > p2_tot) {
        m4mu = sqrt(energy_tot * energy_tot - p2_tot);
    }

    // Final result
    cout << "\n--- Reconstructed 4-Muon System ---" << endl;
    cout << "Total Px:       " << px_tot << " GeV/c" << endl;
    cout << "Total Py:       " << py_tot << " GeV/c" << endl;
    cout << "Total Pz:       " << pz_tot << " GeV/c" << endl;
    cout << "Total Energy:   " << energy_tot << " GeV" << endl;
    cout << "Invariant Mass m_4mu: " << m4mu << " GeV/c^2" << endl;

    return 0;
}