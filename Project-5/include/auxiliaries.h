#ifndef AUXILIARIES_H
#define AUXILIARIES_H

#include <functional>
#include <armadillo>

/// @brief A function that flattens a 2D index, assuming row-filling first, i.e. (i,j) -> i*Nx + j
/// @param i Row index
/// @param j Column index
/// @param Nx Number of grid points in x direction
/// @return Flattened index
size_t flatten_index(size_t i, size_t j, size_t Nx);

/// @brief A function that unflattens a 2D index, assuming row-filling first, i.e. (i,j) -> i*Nx + j
/// @param k Flattened index
/// @param Nx Number of grid points in x direction
/// @return Unflattened index
arma::uvec unflatten_index(size_t k, size_t Nx);

/// @brief A function that finds the discretized step sizes in position dx and dy, given a selected domain and a matrix size to work with.
/// @param Nx Number of grid points in x direction
/// @param Ny Number of grid points in y direction
/// @param x_bound Boundaries in x direction
/// @param y_bound Boundaries in y direction
/// @return A c++ standard tuple containing two doubles for dx and dy
std::tuple<double, double> find_dx_and_dy(size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound);

/// @brief Allows to wrap std::function of general form so that to support caching.
/// @tparam Foutput Function's output type
/// @tparam Cache  Cache type;
/// Cache is supposed to be a first parameter of a function (non-const reference!);
/// User is supposed to write cache usage inside the function manually;
/// After wrapping, cache is fully handled by the class, with possible changes at each call
/// @tparam ...Args Function arguments besides cache
/// You are supposed to put them after Cache&amp; parameter
template <class Foutput, class Cache, class... Args>
class CachedFunc
{
private:
    std::function<Foutput(Cache &, Args...)> func; // callable that may use caching
    Cache cache;                                   // data which should be saved
public:
    /// @brief public constructor of CachedFunc
    CachedFunc(const std::function<Foutput(Cache &, Args...)> &func, Cache defaultcache = Cache()) : func{func}
    {
        erase(defaultcache);
    }
    /// @brief Invokes wrapped function based on cache and provided arguments
    /// @param ...args Function arguments besides cache
    /// @return Foutput from this invocation
    Foutput operator()(Args... args)
    {
        return func(cache, args...);
    }
    /// @brief Returns wrapped function as std::function, with cache running under the hood
    /// @return std::function<Foutput(Args...)>
    operator std::function<Foutput(Args...)>()
    {
        return [this](Args... args)
        { return func(this->cache, args...); };
    }
    /// @brief Erases cache
    /// @param defaultval Value that is substituted inside the cache; equals 'Cache()' by default, pass your version if needed/required
    void erase(Cache defaultval = Cache())
    {
        cache = defaultval;
    }
};

#endif