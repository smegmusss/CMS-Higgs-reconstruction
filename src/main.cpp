/**
 * @file main.cpp
 * @author smegmusss
 * @brief CMS Higgs to 4 muons invariant mass reconstruction (Explicit Math).
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../include/Particle.hpp"

using namespace std;

int main() {

    ifstream file("data/4mu_2012.csv");
    ofstream outFile("output/masses.txt");

    if(!file.is_open()) {
        cout << "Error opening input file!" << endl;
        return 1;
    }
    string header;
    file >> header; // Skipping the header

    // Variables to read the csv file
    double Run, Event, pt1, eta1, phi1, pt2, eta2, phi2, pt3, eta3, phi3, pt4, eta4, phi4;
    char comma;

    int count = 0;

    // Rimossa la prima virgola prima di Run
    while (file >> Run >> comma >> Event >> comma >> pt1 >> comma >> eta1
        >> comma >> phi1 >> comma >> pt2 >> comma >> eta2 >> comma >> phi2 
        >> comma >> pt3 >> comma >> eta3 >> comma >> phi3 >> comma >> pt4 
        >> comma >> eta4 >> comma >> phi4) 
    {
        vector<Particle> muons = {
            Particle(pt1, eta1, phi1),
            Particle(pt2, eta2, phi2),
            Particle(pt3, eta3, phi3),
            Particle(pt4, eta4, phi4)
        };
            
        // Kinematic cut: pt threshold = 5.0
        bool passesCut = true;
        for (const auto& muon : muons) {
            double pt = sqrt(muon.px * muon.px + muon.py * muon.py);
            if (pt < 5.0) {
                passesCut = false;
                break;
            }
        }

        if (!passesCut) {
            continue;
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

        // Salva la massa calcolata sul file per Python
        outFile << m4mu << "\n";
        count++;
    }

    cout << "\n--- Reconstruction Complete ---" << endl;
    cout << "Total processed events saved: " << count << endl;

    return 0;
}
