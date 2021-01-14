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

/****************************** Types ***********************************/
/**
 * @brief embellished optional type. Note: not using std::optional just for the practice of writing templates
 * @tparam A parameterized type of the optional
*/
template<class A>
class Optional {
private:
    bool _is_valid;
    A _value;

public:
    Optional() : _is_valid(false) {};
    Optional(A x) : _is_valid(true), _value(x) {};

    bool is_valid() const {
        return _is_valid;
    }

    A value() const {
        return _value;
    }
};


/****************************** Function Definitions ***********************************/
/**
 * @brief safe square root function that returns an optional. Note: this could also be a template
 * @param x 
 * @return 
*/
Optional<double> safe_root(double x) {
    return (x >= 0) ? Optional<double>{sqrt(x)} : Optional<double>{};
}


/**
 * @brief safe reciprocal function from the exercies
 * @param x 
 * @return 
*/
Optional<double> safe_reciprocal(double x) {
    return (x != 0) ? Optional<double>{1/x} : Optional<double>{};
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
