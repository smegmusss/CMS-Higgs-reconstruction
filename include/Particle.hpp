/**
 * @file Particle.hpp
 * @author smegmusss
 * @brief Lightweight 4-momentum struct for CMS particle analysis.
 */

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <cmath>

using namespace std;

struct Particle {
    double px, py, pz, energy;

    // Converts ROOT (pt, eta, phi) straight to Cartesian (standard muon mass = 0.105...)
    Particle(double pt, double eta, double phi, double mass = 0.105658) {
        px = pt * cos(phi); // pt is the momentum on the xy plane
        py = pt * sin(phi);
        pz = pt * sinh(eta); // eta is the pseudorapidity and sinh is the hyperbolic sin 
        energy = sqrt(px * px + py * py + pz * pz + mass * mass);
    }

    // Overload + 4-momentum addition
    Particle operator+(const Particle& other) const { // other for the second particle
        Particle res;
        res.px = px + other.px;
        res.py = py + other.py;
        res.pz = pz + other.pz;
        res.energy = energy + other.energy;
        return res;
    }

    // Calculates invariant mass m 
    double mass() const {
        double p2 = px * px + py * py + pz * pz;
        return (energy * energy > p2) ? sqrt(energy * energy - p2) : 0.0;
    }

private:
    Particle() : px(0), py(0), pz(0), energy(0) {}
};

#endif // PARTICLE_HPP