# Category: The Essense of Composition
Chapter one of CTFP challenges.

## Implement, as best as you can, the identity function in your favorite language (or the second favorite, if your favorite language happens to be Haskell).

```cpp
/**
 * @brief identity function returns the value of self
 * @return 
*/
template <typename T>
T identity(T&& param){
    return param;
}
```

## Implement the composition function in your favorite language. It takes two functions as arguments and returns a function that is their composition.

I'm not entirely satisfied with this solution, but it works decently for trivial functions provided that the output of G is the input to F. It does struggle with other template functions as arguments, as these need a different instantiation mechanism, but I probably suck too much at templates to really do this well. Probably worth revisiting at some point with a bigger knowledge base.

```cpp
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
```

## Write a program that tries to test that your composition function respects identity.

This is where the above template struggles, as it requires the identity function to be implemented with type int which obviously breaks the generality of the composition. That said, identity as a standalone function taking in a composition of two other functions is totally valid.

```cpp
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
```

## Is the world-wide web a category in any sense? Are links morphisms?
Web-pages are abstract objects, and if a site $A$ contains a link to site $B$, and site $B$ contains a link to site $C$, then there exists a composition $B\circ A$, which goes to $C$ which essentially makes links morphisms.

## Is Facebook a category, with people as objects and friendships as morphisms?
No, because friendships are not composable. I.e.: Bill is not necessarily friends with Fred who is friends with Albert.

## When is a directed graph a category?
If each node in the graph contains an arrow back to itself, and each arrow to other nodes is composable.