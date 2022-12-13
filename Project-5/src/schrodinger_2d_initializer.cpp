#include "../include/schrodinger_2d_initializer.h"
#include "../include/auxiliaries.h"

#include <armadillo>


arma::cx_vec initialize_particle_wavefunction(size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound,
											  double x_center, double y_center, double x_spread, double y_spread, double px, double py)
{
	using namespace std;
	using namespace std::complex_literals;
	// first introduce psi matrix - the digitalized wave function.
	arma::cx_mat psi = arma::zeros<arma::cx_vec>((Nx - 2) * (Ny - 2));

	auto [dx, dy] = find_dx_and_dy(Nx, Ny, x_bound, y_bound);
	double x_min = x_bound(0);
	double y_min = y_bound(0);

	// fill it
	for (size_t i = 0; i < Nx - 2; i++)
	{
		for (size_t j = 0; j < Ny - 2; j++)
		{
			// Connecting physical coordinates x and y to matrix indices. Boundary points excluded.
			double x = x_min + (i + 1) * dx;
			double y = y_min + (j + 1) * dy;
			// Build the large exponent expression given for u() in project spec.
			std::complex<double> exp_1 = -(x - x_center) * (x - x_center) / (2 * (x_spread * x_spread));
			std::complex<double> exp_2 = -(y - y_center) * (y - y_center) / (2 * (y_spread * y_spread));
			std::complex<double> exp_3 = 1i * px * (x - x_center);
			std::complex<double> exp_4 = 1i * py * (y - y_center);

			psi(flatten_index(i, j, Nx - 2)) = exp(exp_1 + exp_2 + exp_3 + exp_4);
		}
	}
	// Finally make sure absolute square of psi is 1, meaning particle is definitely some place, and probability add up to 1.
	psi = psi / arma::norm(psi);

	return psi;
}
