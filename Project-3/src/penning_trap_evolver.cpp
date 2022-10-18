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

		// TODO: Replace external_force_field with total_force once we are ready for multi particle calculations.
		arma::vec force = external_force_field(temp_r, m_particles[i].v, m_particles[i].q);
		double mass = m_particles[i].m;

		m_particles[i].v += force / mass * dt;
	}
}

void PenningTrap::evolve_RK4(double dt)
{
	// TODO: When we come to multi particle interaction, we need a temporary copy of every particle before starting.
	// Quoting task: "since we’ll need the original positions and velocities to perform the final RK4 update step."
	// Also then replace external_force_field with total_force just as with Forward Euler above.

	for (size_t i = 0; i < m_particles.size(); i++)
	{
		std::cout << "Runga Kutta 4 step particle " << i << " at " << m_particles[i].r << " velocity: " << m_particles[i].v << std::endl;
		// Storing copy of position for one particle, to allow stepping r and v in sync (ie stepping v using the corresponding r not the next one).
		arma::vec temp_r = m_particles[i].r;
		arma::vec temp_v = m_particles[i].v;

		double mass = m_particles[i].m;

		// Using the Runga Kutta order 4 formula for coupled equiations.

		//For each particle, compute k_r,1 and k_v,1.
		arma::vec kr1 = dt * m_particles[i].v;
		arma::vec kv1 = dt / mass * external_force_field(m_particles[i].r, m_particles[i].v, m_particles[i].q);

		//For each particle, update the position and velocity using the corresponding k_r,1 and k_v,1.
//		m_particles[i].r = 
//		m_particles[i].v = 

//For each particle, compute k_r,2 and k_v,2.
//... several steps
//Final step: For each particle, perform the proper RK4 update of position and velocity using the original particle position and velocity, together with all the  and  computed above.
/* TODO: work in progress, below is only sketch of algorithm
...
		double kr = (kr1 + 2 * kr2 + 2 * kr3 + kr4) / 6;
...
		double kv1 = h * external_force_field(x0, y0);
		double kv2 = h * external_force_field((x0 + h / 2), (y0 + kv1 / 2));
		double kv3 = h * external_force_field((x0 + h / 2), (y0 + kv2 / 2));
		double kv4 = h * external_force_field((x0 + h), (y0 + kv3));
		double kv = (kv1 + 2 * kv2 + 2 * kv3 + kv4) / 6;
*/

	}
}
