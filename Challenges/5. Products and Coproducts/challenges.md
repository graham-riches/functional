# Products and Coproducts Categories

Chapter five of CTFP challenges.

## Show that the terminal object is unique up to unique isomorphism

If an object is terminal in a category, then there is only a single morphism coming into that object from the preceding object in the category. We can actually take the example from the book that proves that an initial object is unique up to unique isomorphism as that is really the same thing (Products and Coproducts and the duality of all thing category theory).

Take two terminal objects `i1` and `i2`. Since `i1` is terminal, there is a unique morphism `f` from `i2` to `i1`. In a similar manner, there is unique morphism `g` from `i1` to `i2`, as `i2` is also terminal.

Taking the composition of `g` and `f`, we know that that must equal a morphism from `i1` back to `i1`. However, as `i1` is terminal there can only be _one_ morphism from `i1` to `i1`, which must be the identity morphism. So in that case, the composition `g . f` is equal to identity. Therefore in any two terminal objects must be isomorphic!

## What is the product of two objects in a poset? (Hint: use the universal construction)

Recall that a poset is a partially ordered set, meaning that there is a unique ordering of elements in the set with a unique morphism between elements. In this case the morphism is `<` as it is a partially ordered set!


recall that a product in the category theory sense is defined as:


The product of two objects `a` and `b` is the object `c` equipped with two projections such that for any other object `c'` equipped with two projections, there is a unique morphism `m` from `c'` to `c` that factorizes those projections.

What this really means is that the product of two objects is the most reduced form of the combination (pair) or those two objects.


``` Haskell
factorizer :: (c -> a) -> (c -> b) -> (c -> (a, b))
factorizer p q = \x -> (p x, q x)
```

recall that for a partial order, the following holds

```
if a <= b, b <= c, then a <= c
if a <= b and b <= a, then a == b
```

Taking the cartesian product of two sets `X` and `Y`:

$$ X x Y = \{(x,y) | x \in X, y \in Y \}$$

If we consider the set of integers sorted by the `<=` operator, we can see the outcome here:

```
a <= c
b <= c
and
a <= b
```

therefore `c` is either equal to both `a` and `b` (`a == b == c`), or is the next element in the set greater than `b` (`a <= b, c > b`). Another element `c'` could not be the product as that would necessitate that `c' > c`, which is not the best projection of the category.

Another example from [here](https://en.wikiversity.org/wiki/Introduction_to_Category_Theory/Products_and_Coproducts_of_Sets#Divisibility_poset), is the the divisibility poset. Given the syntax `7 | 42` meaning "7 is a factor of 42", we can create the poset rules as:

```
a | a -> a is a factor of a (makes sense)
if a | b, and b | a, then a = b -> if a is a factor of b, and b is a factor of a, they must be equal
if a | b, and b | c, then a | c -> example: 14 | 42, 7 | 14 then 7 | 42, which is correct
```

Let's take as an example the set of numbers that are factors of the integer 30:
$$ x = \{1, 2, 3, 5, 6, 10, 15, 30 \}$$

By applying the above rules, we end up with a tiered hierarchy:

```
30
10 15 6
5 2 3
1
```

take for example the product of the elements 2 and 5 and the rules of our set, C is the next element in the hierarchy which maps to 5 and 2 through the projections `p` and `q`. It turns out that this number is 10, which is the least common multiple of 2 and 5.


## What is the coproduct of two objects in a poset?

reversing the above example, it's the highest valued object that is less than `a` and `b`.

```
c == a == b
c <= a, a <=b
```

from the divisibility example, it would be the greatest common denominator of the values.

`gcd(10,15) = 5`

## Implement the equivalent of Haskell `Either`:

```cpp
#include <iostream>
#include <string>

template <typename Left, typename Right>
class either {
    public:        
        //!< data constructor for Left
        either(const Left& left) {
            container.left = left;
            _left = true;
            std::cout << "constructed an either of Left type" << std::endl;
        }

        //!< data constructor for Right
        either(const Right& right) {
            container.right = right;
            _left = false;
            std::cout << "constructed an either of Right type" << std::endl;
        }
    
        //!< check which value is contained in the either
        bool is_left() const {
            return _left;
        }

        //!< get the Left value
        Left left() const {
            if (_left) {
                return container.left;
            }
            else {
                throw std::logic_error("cannot get Left value from either containing a Right");                
            }
        }

        //!< get the Right value
        Right right() const {
            if (_left) {
                throw std::logic_error("cannot get Right value from either containing a Left");
            } else {
                return container.right;
            }
        }

    private:
        typedef union {
            Left left;
            Right right;
        } EitherContainer;

        EitherContainer container;
        bool _left;
};


int main()
{
    either<int, bool> a{true};
    either<int, bool> b{5};
}

prints:
constructed an either of Right type
constructed an either of Left type

```

## Show that `Either` is a "better" coproduct than `int` equipped with two injections:

```cpp
int i(int n) { return n; }
int j(bool b) { return b ? 0 : 1; }
```

we can create a projection member function using our `either` type as:
```cpp

int m(either<int, bool> const& e) {
    if (e.is_left) {
        return e.left();
    } else {
        return static_cast<int>(!e.right());
    }
}
```

The projection function `m` goes directly from the either coproduct to the output `c`, whereas the functions mapping from `int` to `int` and `bool` to `int` can be re-written in terms of `either` and `m`. Therefore, `either` is the correct coproduct in this situation.

```
i . m = either<int, bool>::left
j . m = either<int, bool>::right
```


## Continuing the previous problem: How would you argue that `int` equipped with the two injections `i` and `j` cannot be "better" than `either`:

If this were true, there would be a factorizing function `m(int)` to `either<int,bool>` that would factorize `i` and `j`. Would this function signature make any sense?

```
Either<int, bool> m(int);
```

nope! How can we take a function of a single argument type and create a compound type `either` without one of the fields in the `either` being completly meaningless? I don't believe we can.

Another way to think of this is:

```Haskell
left =  m . i
left = m . int i(int n) { return n; }
left = m . identity
left = m

right = m . j
right = m . int j(bool b) { return b ? 0 : 1; }
right = m . false(b)
right 0 = m . false(0)
right 0 = m . true


m 1 = left 1 = right false
m 0 = left 0 = right true

```
From above, to create the either we always have to fake one of the values basically.

## Continuing with these injections:

```cpp
int i(int n) {
    if (n < 0) { 
        return n; 
    } else {
        return n + 2;
    }
}

int j(bool b) { return b ? 0 : 1; }
```

The version using either nicely factors `i` and `j`:
```cpp
int m(Either<int, bool> const &e) {
    if (e.is_left) {
        int n = e.left();
        return n + 2;
    } else {
        return static_cast<int>(!e.right());
    }
}
```

following the math above:


```Haskell
left =  m . i
left = m . identity if n < 0
left = m . \n -> n + 2 if n > 0

right = m . j
right = m . int j(bool b) { return b ? 0 : 1; }
right = m . false(b)


m 0 = right true
m 1 = right false

```
NOTE: the left hand side cannot produces values of 1 in the either as it has a conditional jump to `n+2`, which inherently makes the `either` a better option. Another reason would be that it also cannot map `MAX_INT` values into the `either` as it will overflow.
