/*! \file categories.cpp
*
*  \brief some experiments from reading the first chapters of Category Theory for Programmers
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


/****************************** Function Definitions ***********************************/
/**
 * @brief function template to return a memoized version of a function object
 * @tparam Function the function object to memoize
 * @tparam ...Args arguments
 * @return new function object
 * @note the syntax for the function pointer as an argument is somewhat gory, so using an alias or typedef
 *       would be a good idea.
*/
template <typename Function, typename ...Args>
auto memoize(Function (*f)(Args...)){
    std::map<std::tuple<Args...>, Function> cache;

    return [f, cache](Args... args) mutable {
        const auto args_t = std::make_tuple(args...);
        const auto hit = cache.find(args_t);

        Function result;
        if (hit != cache.end()){
            result = hit->second;
        } else {
            result = f(args...);
            cache.insert({args_t, result});            
        }
        return result;
    };
}

/**
 * @brief template decorator class that wraps a function object with a timer for performance measuring
 * @tparam Function the function to wrap
 * @tparam Duration std::chrono::duration type to report the elapsed time in
*/
template <typename Function, typename Duration>
class TimeItDecorator {
public:
    TimeItDecorator(Function f)
    : m_function(f) {};

    template <typename ...Args>
    auto operator() (Args&& ...args){
        auto start = std::chrono::high_resolution_clock::now();
        auto result = m_function(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Elapsed Time: " << std::chrono::duration_cast<Duration>(end - start).count() << "\n";
        return result;
    }

private:
    Function m_function;
};

/**
 * @brief helper function to create a wrapped timed function object
 * @tparam Function the function to wrap
 * @tparam Duration duration type for reporting the elapsed time of the function in
 * @return 
*/
template <typename Function, typename Duration>
TimeItDecorator<Function, Duration> time_it(Function f, Duration d) {
    return TimeItDecorator<Function, Duration>(std::move(f));
}

/**
 * @brief factorial function that is intentionally inefficient for benchmarking the comparison with the memoized version
 * @param n factorial number to calculate
 * @return 
*/
int64_t factorial(int n){
    std::vector<int> iota(n);
    std::iota(iota.begin(), iota.end(), 1);
    return std::accumulate(iota.cbegin(), iota.cend(), int64_t{1}, std::multiplies<int64_t>() );
}

/**
 * @brief main application entry point
 * @param argc number of arguments
 * @param argv pointer to array of inputs
 * @return integer return code
*/
int main( int argc, char *argv[] ) {
    /* wrap the function in the memoize template, which adds caching */
    auto memoized_factorial = memoize(factorial);

    /* wrap the memoized function in a timer that reports the elapsed duration */
    auto timed_factorial = time_it(memoized_factorial, std::chrono::nanoseconds());
    
    /* run the function the first time, which should take a bit longer since the result is not cached */
    auto non_cached = timed_factorial(20);    

    /* repeat with caching */
    auto cached = timed_factorial(20);

    /* cached random number generator with srand setting the seeding */
    std::srand(1);
    auto memoized_random = memoize(std::rand);
    auto timed_random = time_it(memoized_random, std::chrono::nanoseconds());
    auto random_no_cache = timed_random();
    std::srand(1); //!< reseed the generator
    auto random_cache = timed_random();

   return 0;   
}
