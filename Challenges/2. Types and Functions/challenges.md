# Types and Functions
Chapter two of CTFP challenges.

## Define a higher-order function (or a function object) memoize in your favorite language. This function takes a pure function f as an argument and returns a function that behaves almost exactly like f, except that it only calls the original function once for every argument, stores the result internally, and subsequently returns this stored result every time it’s called with the same argument. You can tell the memoized function from the original by watching its performance. For instance, try to memoize a function that takes a long time to evaluate. You’ll have to wait for the result the first time you call it, but on subsequent calls, with the same argument, you should get the result immediately.

This ended up being more complex than expected, but it was very fun to do! Adding the extra timer decorated was a good exercise in templates :)

```cpp
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

   return 0;   
}
```

Produces
```
Elapsed Time: 9100
Elapsed Time: 1900
```

## Try to memoize a function from your standard library that you normally use to produce random numbers. Does it work? Most random number generators can be initialized with a seed. Implement a function that takes a seed, calls the random number generator with that seed, and returns the result. Memoize that function. Does it work?

Combined parts two and three with the existing code from above to get the following (which seems to work as intended).

```cpp
...

/* cached random number generator with srand setting the seeding */
std::srand(1);
auto memoized_random = memoize(std::rand);
auto timed_random = time_it(memoized_random, std::chrono::nanoseconds());
auto random_no_cache = timed_random();
std::srand(1); //!< reseed the generator
auto random_cache = timed_random();

...
```

Produces
```
Elapsed Time: 2800
Elapsed Time: 1700
```

## Which of these C++ functions are pure? Try to memoize them and observe what happens when you call them multiple times: memoized and not.

> a.
```cpp
int fact(int n) {
    int i;
    int result = 1;
    for (i = 2; i <= n; ++i)
    result *= i;
    return result;
}
```

This function is technically pure in that it has no observable side effects and will produde the same output for a given input. This is true even though there is local data mutation (immutability and functional purity are not necessarily the same)

> b. 
```cpp
std::getchar()  
```
100% not pure. This is completely dependent on the IO from the console, which is the farthest thing from pure.


> c. 
```cpp
bool f() {
    std::cout << "Hello!" << std::endl;
    return true;
}
```
Also not pure as there is the side effect of IO. If cached, it will never call the function again, which will never produce the desired side effect.

> d.  
```cpp
int f(int x) {
    static int y = 0;
    25
    y += x;
    return y;
}
```
static values are most definitely not pure.

## How many different functions are there from Bool to Bool? Can you implement them all?

[Link to Haskell info on this](https://stackoverflow.com/questions/18716804/27-different-bool-to-bool-values-in-haskell#:~:text=More%20exactly%20%7CB%7C%20%5E%20%7C,of%20type%20Bool%20%2D%3E%20Bool%20.)

The above link mentions 27, although that seems quite large. If we're not looking at bottoms, then there are only 4:

```cpp
bool id(bool a){
    return a;
}

bool not(bool a){
    return !a;
}

bool always_true(bool a){
    return true;
}

bool always_false(bool b){
    return false;
}
```
