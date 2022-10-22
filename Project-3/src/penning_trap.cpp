
#include "../include/penning_trap.h"
#include "../include/particle.hpp"

#include <functional>
#include <vector>
#include <armadillo>

PenningTrap::PenningTrap(double B0, double V0, double d, const std::vector<Particle> &particles)
    : m_B0(B0), m_V0(V0), m_d(d), m_particles(particles){};

void PenningTrap::enable_particle_interaction(const std::function<arma::vec(const Particle &, const Particle &)> &force)
{
    this->m_force = force;
}

void PenningTrap::add_particle(const Particle &particle)
{
    this->m_particles.push_back(particle);
}

const arma::vec PenningTrap::external_force_field(const arma::vec &r, const arma::vec &v, double q) const
{
    arma::vec F = arma::zeros<arma::vec>(3);
    F(0) = q * (m_V0 / (m_d * m_d) * r(0) + m_B0 * v(2));
    F(1) = q * (m_V0 / (m_d * m_d) * r(1) - m_B0 * v(1));
    F(2) = -2 * q * m_V0 / (m_d * m_d) * r(2);
    return F;
}

const arma::vec PenningTrap::interaction_force_on_a_particle(size_t excluded_particle_index, const Particle &perturbed_particle) const
{
    arma::vec F = arma::zeros<arma::vec>(3);
    for (size_t i = 0; i < m_particles.size(); i++)
        if (i != excluded_particle_index)
            F += m_force(m_particles[i], perturbed_particle);
    return F;
}

const arma::vec PenningTrap::interaction_force_on_a_particle(size_t excluded_particle_index, const arma::vec &perturbed_r, const arma::vec &perturbed_v) const
{
    return interaction_force_on_a_particle(excluded_particle_index, Particle(m_particles[excluded_particle_index].q, m_particles[excluded_particle_index].m, perturbed_r, perturbed_v));
}
