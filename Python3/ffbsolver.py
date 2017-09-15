#!/usr/bin/env python3
#-*- coding: utf-8 -*-

# Fibonacci "Fizz Buzz" Solver.
# Generate the first n Fibonacci numbers F(n), printing
#     "Buzz" when F(n) is divisible by 3.
#     "Fizz" when F(n) is divisible by 5.
#     "FizzBuzz" when F(n) is divisible by 15.
#     "BuzzFizz" when F(n) is prime.
#   the value F(n) otherwise.

import argparse
import sys
from math import sqrt
import pdb

class Primes:
    "Progressively grown list of prime numbers."
    def __init__(self):
        self.primes = [ 2, 3 ]
        self.lastodd = self.primes[-1]

    def oddSeries(self):
        "Generate all odd numbers, starting at 5."
        odd = 5
        while True:
            yield odd
            odd += 2

    def isPrime(self, candidate):
        "Return True if candidate is prime, else False."
        if candidate == 1:
            return False
        if candidate <= self.primes[-1] and candidate in self.primes:
            return True
        for divisor in self.primes:
            if candidate % divisor == 0:
                # not prime
                return False
        # got here? then it's prime.
        return True

    def stretch(self, limit):
        "Stretch list of primes to given limit."

        if limit < self.lastodd:
            return  # too soon to stretch
        while True:
            self.lastodd += 2
            if self.isPrime(self.lastodd):
                self.primes.append(self.lastodd)
            if self.lastodd >= limit:
                return

def classify(value, primes):
    #   "Buzz" when F(n) is divisible by 3.
    #   "Fizz" when F(n) is divisible by 5.
    #   "FizzBuzz" when F(n) is divisible by 15.
    #   "BuzzFizz" when F(n) is prime.
    #   the value F(n) otherwise.

    primes.stretch(int(sqrt(value)))

    # look for desired divisors,
    msgs = []
    if value % 5 == 0:  # divisible by 5
        msgs.append("Fizz5")
    if value % 3 == 0:  # divisible by 3
        msgs.append("Buzz3")
    if value % 15 == 0: # divisible by 15
        msgs.append("FizzBuzz15")
    if primes.isPrime(value):
        msgs.append ("BuzzFizzP")

    if msgs:
        msg = ' '.join(msgs)
    else:
        msg = "%d" % value

    return msg


def fibsequence(N):
    """Generate sequence of Fibonacci numbers up to the
    'N'th member of the sequence."""

    x = 0
    y = 1
    count = 0
    while count < N:
        x, y = y, x + y
        count += 1
        yield x
        # x = F(count)


def parseargs(argv):
    "Parse command line arguments."

    desc = "Fibonacci Fizz Buzz solver"
    parser = argparse.ArgumentParser(description=desc)
    parser.add_argument('N', type=int,
        help="Last Fibonacci number to consider")
    parser.add_argument('-v', '--verbose', help="enable verbose output",
        action="store_true")

    pdb.set_trace()
    args = parser.parse_args()
    return args


def main(argv):

    args = parseargs(argv)

    primes = Primes()

    for fn in fibsequence(args.N):
        # fn is F(n)
        if args.verbose:
            print(fn, end=' ')          # prepend result by number and blank.
        print(classify(fn, primes))


sys.exit(main(sys.argv))

# vim: set sw=4 tw=80 :
