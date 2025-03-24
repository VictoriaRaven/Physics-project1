#include <iostream>
#include <cmath>
using namespace std;

/*
The K^0 meson is a subatomic partical of rest mass k_k=498 MeV/c^2 that decays 
into two charged pions, K^0 -> ((pi)^+) + ((pi^-). (The ((pi)^+) and ((pi^-) 
have opposite charges but exactly the same mass of m_(pi) = 140 MeV/c^2). 
A K^0 at rest decays into two pions. User conservation of energy and momentum 
to find the energies, momenta, and speeds of the two pions.  To help out with 
writing a code to make the equations and calculate it, the answer key to this 
problem says that ((pi)^+) should be about equal to 0.827 c   and ((pi^-) 
should be about equal to -0.827 c. 

*/

// calculator is here
// I will modify this so that it is more correct.
// Year: 2023

#include <iostream>
#include <cmath>

using namespace std;

// Calculate Lorentz factor (gamma)
double lorentzFactor(double v) {
    return 1.0 / sqrt(1 - (v * v));
}

// Calculate energy of a particle with mass and velocity inputed
double energy(double mass, double v) {
    double gamma = lorentzFactor(v);
    return mass * gamma;  
    // E = m * gamma * c^2, but c = 1 in natural units
}

// Calculate momentum of a particle with energy and mass inputed
double momentum(double energy, double mass) {
    return sqrt(energy * energy - mass * mass); 
    // p = sqrt(E^2 - m^2)
}

// Calculate velocity of particle with momentum and mass inputed
double velocity(double momentum, double mass) {
    return momentum / (mass * lorentzFactor(0)); 
    // v = p / (m * gamma)
}

int main() {
    // vars for user input
    double m_K, m_pi;

    // User input: masses of the K^0 meson and pi mesons
    cout << "Enter the mass of the K^0 meson in MeV/c^2: ";
    cin >> m_K;

    cout << "Enter the mass of the pi mesons (pi^+ and pi^-) in MeV/c^2: ";
    cin >> m_pi;

    // Energy of the K^0 meson at rest
    double E_K = m_K;

    // Total conserved energy of system
    // After decay energy is shared by 2 pions.
    double E_pi = E_K / 2.0;

    // Momentum per pion: E^2 = p^2 + m^2 (in units of c=1)
    double p_pi = momentum(E_pi, m_pi);

    // Velocity per pion: v = p / E
    double v_pi = p_pi / E_pi;

    // Convert speed to fraction of c
    double v_pi_fraction_c = v_pi; // In terms of c (since we used c=1)
    
    // Calc/Print
    cout << "\nResults:\n";
    cout << "Approximate Energy per pion (E_pi): " << E_pi << " MeV" << endl;
    cout << "Approximate Momentum per pion (p_pi): " << p_pi << " MeV/c" << endl;
    cout << "Approximate Speed of per (v_pi): +/-" << v_pi_fraction_c << " c" << endl;
    
    //following the problem user should input: 
    //m_K = 498.0; // Mass of K^0 meson in MeV/c^2
    //m_pi = 140.0; // Mass of each pi meson in MeV/c^2

    return 0;
}
