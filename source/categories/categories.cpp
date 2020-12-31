/*! \file categories.cpp
*
*  \brief some experiments from reading the first chapters of Category Theory for Programmers
*
*  \author Graham Riches
*/


/********************************** Includes *******************************************/
#include <iostream>
#include <utility>


/****************************** Function Definitions ***********************************/
/**
 * @brief identity function returns the value of self
 * @return 
*/
template <typename T>
T identity(T&& param){
    return param;
}

/**
 * @brief takes a function of type F, a function of type G, and a set of arguments and returns a composed function object
 * @param F first function taking an argument of decltype(G(args...))
 * @param G second function taking an argument of (args...)
 * @param ...Args list of arguments
 * @return composed function object
*/
template <typename F, typename G, typename ...Args>
auto compose(F&& f, G&& g, Args... args){
    auto function = [f, g, args...](){return f(g(args...));};
    return function;
}

/**
 * @brief dumb test function for trying the compose template 
*/
int plus_one(int arg){
    return arg + 1;
};

/**
* @brief dumb test function for trying the compose template 
*/
int multiply_by_two(int arg){
    return arg * 2;
}


/**
 * @brief main application entry point
 * @param argc number of arguments
 * @param argv pointer to array of inputs
 * @return integer return code
*/
int main( int argc, char *argv[] )
{       
   const int temp{1};   
   std::cout << "Identity of " << temp << " is " << identity(temp) << "\n";

   auto func = compose(plus_one, multiply_by_two, 5);
   std::cout << "Composed function value: " << func() << "\n";

   /* composing with identity requires instantiating the identity type explicitely, which is bad */
   auto test = compose(identity<int>, multiply_by_two, 5);
   bool is_valid_composition = test() == 10;
   std::cout << "Composed function with identity is valid: " << is_valid_composition << "\n";

   /* applying identity to another function object is however, totally valid */
   auto identity_of_function = identity(func);
   std::cout << "Identity of a function is just the function: " << identity_of_function() << "\n";
   return 0;   
}

