#include "../include/penning_trap.h"
#include "../include/particle.hpp"

#include <functional>
#include <vector>
#include <armadillo>

void PenningTrap::evolve_forward_Euler(double dt)
{
	auto particles_temp = m_particles;
	for (size_t i = 0; i < m_particles.size(); i++)
	{
		// std::cout << "Forward Euler on particle " << i << " at " << m_particles[i].r << " velocity: " << m_particles[i].v << std::endl;
		// arma::vec temp_r = m_particles[i].r;
		particles_temp[i].r += dt * m_particles[i].v;

		// TODO: Replace external_force_field with total_force once we are ready for multi particle calculations.
		arma::vec force = total_force_on_a_particle(i, m_particles[i].r, m_particles[i].v);
		double mass = m_particles[i].m;

		particles_temp[i].v += dt / mass * force;
	}
	m_particles = particles_temp;
}

void PenningTrap::evolve_RK4(double dt)
{
	// TODO: When we come to multi particle interaction, we need a temporary copy of every particle before starting.
	// Quoting task: "since we’ll need the original positions and velocities to perform the final RK4 update step."
	// Also then replace external_force_field with total_force just as with Forward Euler above.
	
	for (size_t i = 0; i < m_particles.size(); i++)
	{
		// std::cout << "Runga Kutta 4 step particle " << i << " at " << m_particles[i].r << " velocity: " << m_particles[i].v << std::endl;
		//  Storing copy of position for one particle, to allow stepping r and v in sync (ie stepping v using the corresponding r not the next one).
		arma::vec temp_r = m_particles[i].r;
		arma::vec temp_v = m_particles[i].v;

		double mass = m_particles[i].m;

		// Using the Runga Kutta order 4 formula for coupled equiations.

		// For each particle, compute k_r,1 and k_v,1.
		arma::vec kr1 = dt * m_particles[i].v;
		arma::vec kv1 = dt / mass * total_force_on_a_particle(i, m_particles[i].r, m_particles[i].v);

		// For each particle, update the position and velocity using the corresponding k_r,1 and k_v,1.
		m_particles[i].r += kr1 / 2;
		m_particles[i].v += kv1 / 2;

		// For each particle, compute k_r,2 and k_v,2.
		arma::vec kr2 = dt * m_particles[i].v;
		arma::vec kv2 = dt / mass * total_force_on_a_particle(i, m_particles[i].r, m_particles[i].v);

		// For each particle, update the position and velocity using the corresponding k_r,2 and k_v,2.
		m_particles[i].r = temp_r + kr2 / 2;
		m_particles[i].v = temp_v + kv2 / 2;

		// For each particle, compute k_r,3 and k_v,3.
		arma::vec kr3 = dt * m_particles[i].v;
		arma::vec kv3 = dt / mass * total_force_on_a_particle(i, m_particles[i].r, m_particles[i].v);

		// For each particle, update the position and velocity using the corresponding k_r,3 and k_v,3.
		m_particles[i].r = temp_r + kr3 / 2;
		m_particles[i].v = temp_v + kv3 / 2;

		// For each particle, compute k_r,4 and k_v,4.
		arma::vec kr4 = dt * m_particles[i].v;
		arma::vec kv4 = dt / mass * total_force_on_a_particle(i, m_particles[i].r, m_particles[i].v);

		arma::vec kv = (kv1 + 2 * kv2 + 2 * kv3 + kv4) / 6;
		arma::vec kr = (kr1 + 2 * kr2 + 2 * kr3 + kr4) / 6;

		// Final step: For each particle, perform the proper RK4 update of position and velocity using the original particle position and velocity, together with all the k_r and k_v computed above.
		m_particles[i].r = temp_r + kr;
		m_particles[i].v = temp_v + kv;
	}
}