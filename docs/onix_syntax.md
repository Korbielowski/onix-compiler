# Onix Syntax Documentation

## Introduction to variables

First we have to specify varaible type, we can choose from `int`, `double`, `string`, `boolean`. Than we write variable name, it can't start with numbers or special characters and can't be split with blank space eg. `int 3bad`, `string ]par`, `double h o`. We should start our variable names only with letters, but numbers or _ character can be used in the body of the name eg. `int foo`, `double foo_two`, `string hi2`. At the end we specify variable value like `21` for integers or `True` for booleans.


<Proper ranges for int and double types>

* ### Integer `int`

    Integer `int` variables hold only whole numbers in the range from -256 to 255.

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

    `=` operator is used for assigning values or expresions to variables eg. `int a = 1;`

* ### Arithmetic operators (+, -, *, /)

    `+` operator is used for addition eg. `a = 1 + 2;`
    `-` operator is used for substraction `b = 3 - 1;`
    `*` operator is used for multiplication `d = 2 * 2;`
    `/` operator is used for division `e = 4 / 2`;

* ### Comparison operators (==, !=, >, <, >=, <=)

    These are used to compare two variables in `if`, `elif` statements and in `for`, `while` loops eg. `if(a >= 2)`.
  
* ### Logical operators (or, and)

    Those two operators are used when we want separate expressions to both return True values in the case of `and` operator and if only one of them must return True and other can return False in the case of `or`. These operators are used in `if`, `elif` statements and in `for`, `while` loops.
    
<!-- * ### Comma operator (,) -->

* ### Semicolon operator (; )

    Semicolon has two types of uses, in for loops and at the and of every line of code, we use it as in C++ or C languages.


## If, else and elif statements

* ### If

    We declare `if` by writing `if(exprression){block of code}` when we want to compare something and based on the logical outcome execute some block of code or not, expression inside of parenthesis must return boolean `True` or `False` value, when the return type of expression is not `True` or `False` an exception will occur.

* ### Elif

    We use `elif` when we want to check something in the case of `if` block not executing eg. `elif(expression){block of code}`.

* ### Else

    We use `else` when the other statements `if` or/and `elif` were not executed eg. `else{block of code}`.

## For and while loops

* ### For loops

    We declare for loops by typing `for(some variable; do until; increment variable){block of code}` eg. `for(int i=0; i<10; i++){ j += 1}` when we want to exacute some block of code n times or want to iterate through an array.

* ### While loops

    The usage of the while loop is the same as the for loop, but the way we declare it in our code is different `while(do until){block of code}` eg. `while(True){i += 1}`.