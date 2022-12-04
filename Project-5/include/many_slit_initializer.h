#ifndef MANY_SLIT_INITIALIZER_H
#define MANY_SLIT_INITIALIZER_H

#include <armadillo>

/// @brief Setup for initializing a many slit potential. Slits are centered along y-axis, and are equally spaced.
/// @param x x coordinate considered
/// @param y y coordinate considered
/// @param slit_center_x central position of a slit wall (along x axis)
/// @param slit_center_y central position of a slit wall (along y axis)
/// @param slit_width_x width of a slit wall (along x axis)
/// @param slit_width_y width of a single slit (along y axis)
/// @param slit_spacing spacing between slits (along y axis)
/// @param slit_number number of slits
/// @param scale "amplitude" of potential
/// @return potential at given (x,y) coordinate
double many_slit_potential(double x, double y, double slit_center_x, double slit_center_y, double slit_width_x, double slit_width_y, double slit_spacing, size_t slit_number, double scale);

#endif