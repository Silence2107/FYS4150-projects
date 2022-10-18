#include "../include/penning_trap.h"
#include "../include/particle.h"

#include <functional>
#include <vector>
#include <armadillo>

void PenningTrap::evolve_forward_Euler(double dt)
{
	for (size_t i = 0; i < m_particles.size(); i++)
	{
		std::cout << "Forward Euler on particle " << i << " at " << m_particles[i].r << " velocity: " << m_particles[i].v << std::endl;
		arma::vec temp_r = m_particles[i].r;
		m_particles[i].r += m_particles[i].v * dt;

        //TODO: Replace external_force_field with total_force once we are ready for multi particle calculations.
		arma::vec force = external_force_field(temp_r, m_particles[i].v, m_particles[i].q);
		double mass = m_particles[i].m;
		
		m_particles[i].v += force / mass * dt;
	}
}
