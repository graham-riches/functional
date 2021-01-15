/*! \file kleisli_categories.cpp
*
*  \brief exercises from Chapter 4 - Kleisli Categories
*
*  \author Graham Riches
*/


/********************************** Includes *******************************************/
#include <iostream>
#include <utility>
#include <map>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <vector>
#include <ranges>
#include <chrono>
#include <cstdlib>
#include <optional>

/****************************** Types ***********************************/


/****************************** Function Definitions ***********************************/
/**
 * @brief safe square root function that returns an optional. Note: this could also be a template
 * @param x 
 * @return 
*/
std::optional<double> safe_root(double x) {
    return (x >= 0) ? std::make_optional<double>(sqrt(x)) : std::make_optional<double>();
}


/**
 * @brief safe reciprocal function from the exercies
 * @param x 
 * @return 
*/
std::optional<double> safe_reciprocal(double x) {
    return (x != 0) ? std::make_optional<double>(1/x) : std::make_optional<double>();
}


/**
 * @brief monad bind defined for std optionals to allow composition/ chaining
 * @tparam T 
 * @tparam F 
 * @param opt 
 * @param f 
 * @return 
*/
template <typename T, typename F>
auto mbind(const std::optional<T>& opt, F f) -> decltype(f(opt.value())) {
    if (opt) {
        return f(opt.value());
    } else {
        return {}
    }
}

/**
* @brief main application entry point
* @param argc number of arguments
* @param argv pointer to array of inputs
* @return integer return code
*/
int main( int argc, char *argv[] ) {

    return 0;   
}
