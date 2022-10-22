#ifndef PENNING_TRAP_H
#define PENNING_TRAP_H

#include "particle.hpp"

#include <functional>
#include <vector>
#include <armadillo>
#include <cmath>

/// @brief Class that provides Penning trap functionality.
class PenningTrap
{
private:
    /// @brief Magnetic field strength
    double m_B0;
    /// @brief Voltage
    double m_V0;
    /// @brief Characteristic distance between plates
    double m_d;
    /// @brief Particles in the trap
    std::vector<Particle> m_particles;
    /// @brief Function that computes the interaction force from a first particle to a second particle.
    /// Interaction is assumed to be between no more than 2-particles
    std::function<arma::vec(const Particle &, const Particle &)> m_force;
public:
    /// @brief initializes the trap with the given parameters
    /// @param B0 magnetic field strength
    /// @param V0 voltage
    /// @param d distance between plates
    /// @param particles particles in the trap (absent by default)
    PenningTrap(double B0, double V0, double d, const std::vector<Particle> &particles = std::vector<Particle>());
    /// @brief specifies the force function
    /// @param force force function from the first particle applied to the second particle
    void enable_particle_interaction(const std::function<arma::vec(const Particle &, const Particle &)>& force);
    /// @brief adds a particle to the trap
    /// @param particle particle to add
    void add_particle(const Particle &particle);

    /// @brief access to the external electric field on the particle
    const double &B0() const { return m_B0; };
    /// @brief access to the external magnetic field on the particle
    double &B0() { return m_B0; };
    /// @brief access to the voltage
    const double &V0() const { return m_V0; };
    /// @brief access to the voltage
    double &V0() { return m_V0; };
    /// @brief access to the distance between plates
    const double &d() const { return m_d; };
    /// @brief access to the distance between plates
    double &d() { return m_d; };
    /// @brief access to the particles in the trap (read-only)
    const std::vector<Particle> &particles() const { return m_particles; };

    /// @brief calculates the external force field from the trap
    /// @param r position of a particle for which the force is calculated
    /// @param v velocity of a particle for which the force is calculated
    /// @param q charge of a particle for which the force is calculated
    /// @return external force field from the trap
    const arma::vec external_force_field(const arma::vec &r, const arma::vec &v, double q) const;
    /// @brief calculates the interaction force field on the particle in the trap
    /// @param excluded_particle_index index of the particle in the trap, which we exclude from the calculation (the one that we calculate the force on)
    /// @param perturbed_r perturbed position of a particle for which the force is calculated
    /// @param perturbed_v perturbed velocity of a particle for which the force is calculated
    /// @return interaction force field on the particle
    const arma::vec interaction_force_on_a_particle(size_t excluded_particle_index, const arma::vec &perturbed_r, const arma::vec &perturbed_v) const;
    /// @brief calculates the total force field on the particle in the trap
    /// @param excluded_particle_index index of the particle in the trap, which we exclude from the calculation (the one that we calculate the force on)
    /// @param perturbed_particle particle for which the force is calculated (you may want to pass different positions and velocities here)
    /// @return total force field on the particle
    const arma::vec interaction_force_on_a_particle(size_t excluded_particle_index, const Particle &perturbed_particle) const;

    /// @brief The total force on particle_i from both external fields and other particles
    /// @param excluded_particle_index index of the particle in the trap, which we exclude from the calculation (the one that we calculate the force on)
    /// @return total force field on the particle
    arma::vec total_force(int excluded_particle_index);
    /// @brief Evolve the system one time step (dt) using Runge-Kutta 4th order
    /// @param excluded_particle_index Time step to advance the solution
    void evolve_RK4(double dt);
    /// @brief Evolve the system one time step (dt) using Forward Euler
    /// @param excluded_particle_index Time step to advance the solution
    void evolve_forward_Euler(double dt);

    /// @brief Amount of particles within trap's reach
    /// @return amount of particles within trap's reach
    size_t particle_numbers();
};

#endif
