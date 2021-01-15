# Kleisli Categories
Chapter four of CTFP challenges.

## Construct the Kleisli category for partial functions (define composition and identity)

From the book:
```
A function that is not defined for all possible values of its argument is
called a partial function. It’s not really a function in the mathematical
sense, so it doesn’t fit the standard categorical mold. It can, however, be
represented by a function that returns an embellished type optional:
```

```cpp
template<class A> class optional {
    bool _isValid;
    A _value;
public:
    optional() : _isValid(false) {}
    optional(A v) : _isValid(true), _value(v) {}
    bool isValid() const { return _isValid; }
    A value() const { return _value; }
};
```

Composition can be defined largely by using the monadic bind for optionals from the Functional Programming in C++ textbook. This chains a function taking a value with an optional from a previous execution and is a monad.

```cpp
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
        return {};
    }
}
```

Identity is fairly obvious, and can probably be even more general (i.e. drop the optional?)

```cpp
/**
 * @brief identity for optionals
 * @tparam T 
 * @param x 
 * @return 
*/
template<typename T>
std::optional<T> identity(std::optional<T> &x){
    return x;
}

/**
 * @brief alternative more generic identity
 * @tparam T 
 * @param x 
 * @return 
*/
template <typename T>
T identity(T &x) {
    return x;
}
```



## Implement the embellished function safe_reciprocal that returns a valid reciprocal of its argument, if it’s different from zero.

```cpp
/**
 * @brief safe reciprocal function from the exercies
 * @param x 
 * @return 
*/
std::optional<double> safe_reciprocal(double x) {
    return (x != 0) ? std::make_optional<double>(1/x) : std::make_optional<double>();
}
```

## Compose the functions safe_root and safe_reciprocal to implement safe_root_reciprocal that calculates sqrt(1/x) whenever possible.

```cpp
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
        return {};
    }
}

/**
 * @brief composed function for safe root reciprocal using monad bind
 * @param x 
 * @return 
*/
std::optional<double> safe_root_reciprocal(double x){
    return mbind(safe_reciprocal(x), safe_root);
}
```