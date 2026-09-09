/**
 * @file main.cpp
 * @author smegmusss
 * @brief CMS Higgs to 4 muons invariant mass reconstruction 
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

    if (!file.is_open()) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    string header;
    getline(file, header); // Skipping the header line

    // Variables to read the csv file 
    double Run, Event;
    double PID1, E1, px1, py1, pz1, pt1, eta1, phi1, Q1;
    double PID2, E2, px2, py2, pz2, pt2, eta2, phi2, Q2;
    double PID3, E3, px3, py3, pz3, pt3, eta3, phi3, Q3;
    double PID4, E4, px4, py4, pz4, pt4, eta4, phi4, Q4;
    double mZ1, mZ2, M;
    char comma;

    int count = 0;

    // Reading all variables a
    while (file >> Run >> comma >> Event >> comma 
                >> PID1 >> comma >> E1 >> comma >> px1 >> comma >> py1 >> comma >> pz1 >> comma >> pt1 >> comma >> eta1 >> comma >> phi1 >> comma >> Q1 >> comma
                >> PID2 >> comma >> E2 >> comma >> px2 >> comma >> py2 >> comma >> pz2 >> comma >> pt2 >> comma >> eta2 >> comma >> phi2 >> comma >> Q2 >> comma
                >> PID3 >> comma >> E3 >> comma >> px3 >> comma >> py3 >> comma >> pz3 >> comma >> pt3 >> comma >> eta3 >> comma >> phi3 >> comma >> Q3 >> comma
                >> PID4 >> comma >> E4 >> comma >> px4 >> comma >> py4 >> comma >> pz4 >> comma >> pt4 >> comma >> eta4 >> comma >> phi4 >> comma >> Q4 >> comma
                >> mZ1 >> comma >> mZ2 >> comma >> M) 
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

        // Save the result
        outFile << m4mu << "\n";
        count++;
    }

    // Final result
    cout << "\n--- Reconstruction Complete ---" << endl;
    cout << "Total processed events saved: " << count << endl;

    return 0;
}
