README for Fibbonacci Fizz Buzz Solvers
=======================================

This directory contains a couple of proposed solutions a small coding
challenge, specifically "Fibbonacci Fizz Buzz" (FFB) solvers.
The solutions are in Python and C++.

The problem is intriguing enough that I'll probably continue enhancing it
for a while.
Among other things, it is a place to explore and improve
software engineering "best practices."
(Okay, that may take some time.)

Problem statement and issues
----------------------------

Specifically, it addresses this problem:

  In the programming language of your choice, write a program
  generating the first n Fibonacci numbers F(n), printing

  * "Buzz" when F(n) is divisible by 3.
  * "Fizz" when F(n) is divisible by 5.
  * "FizzBuzz" when F(n) is divisible by 15.
  * "BuzzFizz" when F(n) is prime.
  * the value F(n) otherwise.

There are a couple of interpretations to this problem statement.

One interpretation is to print one of the above. In that case,
entries for "Buzz" (3), "Fizz" (5), and "FizzBuzz" (15)
are mutually exclusive; at most, one of those can be chosen.

Another is to print all those that match.
Thus, if "FizzBuzz" (15) is printed, then so are "Buzz" (3) and "Fizz" (5).

In practice, the implementer should go back to the person providing the
requirements and ask for clarification.
However, that is not an option here, and in any case wasn't the main point
of the problem.

Implementations
---------------

A couple of largely equivalent implementations are provided.

  * The first solution was written in Python 3, and includes an
    odd number generator `oddSeries()`.
    This helps ensure that each generated number is consumed only once.
    A second generator `fibsequence`
    computes and generates a finite sequence of Fibonacci numbers.

  * The second solution is written in C++, with the expectation that
    it is more likely than Python to be used in an embedded system.
    It utilizes `<vector>` from the C++ STL; whether such would be
    done in an embedded system is debatable, but it provides a
    framework for using iterables in C++.

A potential solution in C, utilizing `malloc()`/`free()` for the
array of primes was considered, and then discarded.

Discussion
----------

The Python solution was crafted first,
simply due to ease of expression and development speed.
The C++ solution was crafted next,
mapping the Python list onto a C++ vector.
Naturally, more attention was paid to variable scope in C++.

