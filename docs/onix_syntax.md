# Onix Syntax Documentation

## Introduction to variables

First we have to specify varaible type, we can choose from `int`, `double`, `string`, `boolean`. Than we write variable name, it can't start with numbers or special characters and can't be split with blank space eg. `int 3bad`, `string ]par`, `double h o`. We should start our variable names only with letters, but numbers or _ character can be used in the body of the name eg. `int foo`, `double foo_two`, `string hi2`. At the end we specify variable value like `21` for integers or `True` for booleans.


<Proper ranges for int and double types>

* ### Integer `int`

    Integer `int` variables hold only whole numbers in the range from -1024 to 1024.

    Example how we can declare `int` variable: `int a = 10;`.

    `int` works with all [arithmetic](#arithmetic-operators) and [comparison](#comparison-operators) operators.

* ### Double `double`

    Double `double` stores floating point numbers in the range form ... to ...

    Example of double variable: 
    
    `double b = 10.6;`

* ### String `string`

    String `string` holds characters as an array.
    To declare `string` we can use sigle or double quote like this: 
    
    `string c = "Hello";` or `string c = 'world';`

* ### Boolean `boolean`

    Boolean variables can only store True or False values, remember that the first letter of those two keywords must be capital.

    `boolean d = True;` or `boolean d = False;`

## Operators

* ### Assignment operator (=)

* ### Arithmetic operators (+, -, *, /)

* ### Comparison operators (==, !=, >, <, >=, <=)
  
* ### Logical operators (&, |)

* ### Comma operator (,)

* ### Semicolon operator (;)


## If, else and elif statements

## For and while loops

* ### For loops

* ### While loops