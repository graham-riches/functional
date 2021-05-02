# Simple Algebraic Data Types

Chapter six of CTFP challenges.

## Show the isomorphism between between `Maybe a` and `Either () a`

```Haskell
eitherFromMaybe :: Maybe a -> Either () a
eitherFromMaybe (Just x) = Right x
eitherFromMaybe Nothing = Left ()

maybeFromEither :: Either () a -> Maybe a
maybeFromEither (Right x) = Just x
maybeFromEither (Left ()) = Nothing

```


## Implement the following shape class definition from Haskell in C++ using an interface with virtual functions

```Haskell
area :: Shape -> Float
area (Circle r) = pi * r * r
area (Rectangle d h) = d * h

```

```cpp
constexpr float pi = 3.1415926;

/**
 * \brief shape interface
 */
struct IShape {    
    virtual float area() = 0;
    ~Shape() {}
};

/**
 * \brief circle type
 */
struct Circle : public IShape {
    Circle(float radius)
    : radius(radius) {}

    float area() {
        return pi * radius * radius;
    }

    float radius;
};

/**
 * \brief rectangle type
 */
struct Rectangle : public IShape {
    Rectangle(float length, float width)
    : length(length)
    , width(width) {}

    float area() {
        return length * width;
    }

    float length;
    float width;
};
```


## Continuing with the previous example, add a new function `circumference` 

The Haskell implementation:

```Haskell
circumference :: Shape -> Float
circumference (Circle r) = 2.0 * pi * r
circumference (Rectangle d h) = 2.0 * (d + h)
```

The C++ implementation:
```cpp
constexpr float pi = 3.1415926;

/**
 * \brief shape interface
 */
struct IShape {    
    virtual float area() = 0;
    virtual float circumference() = 0;
    ~Shape() {}
};

/**
 * \brief circle type
 */
struct Circle : public IShape {
    Circle(float radius)
    : radius(radius) {}

    float area() {
        return pi * radius * radius;
    }

    float circumference() {
        return 2.0 * radius * pi;
    }

    float radius;
};

/**
 * \brief rectangle type
 */
struct Rectangle : public IShape {
    Rectangle(float length, float width)
    : length(length)
    , width(width) {}

    float area() {
        return length * width;
    }

    float circumference() {
        return 2.0 * (length + width);
    }

    float length;
    float width;
};
```

Note: this required modifying basically everything: the interface definition, and both derived classes. The Haskell version makes it really simply to add new polymorphic types to a type class

## Continuing further, add a new type Square
Haskell versions

```Haskell
area :: Shape -> Float
area (Circle r) = pi * r * r
area (Rectangle d h) = d * h
area (Square w) = d * d


circumference :: Shape -> Float
circumference (Circle r) = 2.0 * pi * r
circumference (Rectangle d h) = 2.0 * (d + h)
circumference (Square d) = 4.0 * d
```

C++ Versions:
```cpp
struct Square : public IShape {
    Square(float size)
    : size(size) {}

    float area() {
        return size * size;
    }

    float circumference() {
        return 4.0 * size;
    }

    float size;
};

};

```

Required adding a new class definition, whereas Haskell required only adding new pattern matches to the existing functions. 

## Show that `a + a = 2 x a` holds for types (up to isomorphism). Remember that 2 corresponds to Bool

Really not sure I understand this section that well

```Haskell
0         : Void
1         : ()
a + b     : Either a b = Left a | Right b
a x b     : (a, b) or Pair a b = Pair a b
2 = 1 + 1 : data Bool = True | False
1 + a     : data Maybe = Nothing | Just a

```

can show the two isomorphisms:

```Haskell
leftToRight :: Either a a -> (Bool, a)
leftToRight (Left a) = (False, a)
leftToRight (Right a) = (True, a)


rightToLeft :: (Bool, a) -> Either a a
rightToLeft (True, a) = Right a
rightToLeft (False, a) = Left a
```
