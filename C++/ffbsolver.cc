//
//  main.cpp
//  swiftfib-c++
//
//  Created by Rick Kwan on 9/13/17.
//  Copyright © 2017 Rick Kwan. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

class Primes {
  private:
    vector <long> primeslist;
  public:
    Primes(int sz);
    ~Primes();
    bool isPrime(long candidate);
    void stretch(long limit);
  private:
    long lastodd;     // some recent odd number
};

Primes::Primes(int sz)
{
    primeslist.reserve(sz);
    primeslist.push_back(2);
    primeslist.push_back(3);
    lastodd = *primeslist.end();
}

Primes::~Primes() { }

bool
Primes::isPrime(long candidate)
{
    if (candidate == 1)
        return false;
    
    long lastprime = primeslist.back();
    if (candidate <= lastprime) {
        for (auto it=primeslist.begin(); it != primeslist.end(); ++it)
            if (candidate == *it)
                return true;
    }
    long divisor;
    for (auto itdiv=primeslist.begin(); itdiv != primeslist.end(); ++itdiv) {
        divisor = *itdiv;
        if (candidate % divisor == 0)
            return false;
    }
    // got here? then candidate is prime
    return true;
}

void
Primes::stretch(long limit)
{
    if (limit < lastodd)
        return;
    while (true) {
        lastodd += 2;
        if (isPrime(lastodd))
            primeslist.push_back(lastodd);
        if (lastodd >= limit)
            return;
    }
}


long
figseq_next()
{
    static long x = 0;      // current Fib value to return
    static long y = 1;      // next Fib value
    long newy = x + y;
    x = y;
    y = newy;
    return x;
}

string
classify(long value, Primes* primes)
{
    vector <string> msgs;

    primes->stretch(int(sqrt(value)));

    if (value  % 5 == 0)            // divisible by 5
        msgs.push_back("Fizz5");
    if (value % 3 == 0)             // divisible by 3
        msgs.push_back("Buzz3");
    if (value % 15 == 0)            // divisible by 15
        msgs.push_back("FizzBuzz15");
    if (primes->isPrime(value))      // check for primeness
        msgs.push_back("BuzzFizzP");

    string msgline = "";
    if (msgs.size() != 0) {
        string first = *msgs.begin();
        msgline = string(first);
        msgs.erase(msgs.begin());
        for (auto itmsgs = msgs.begin(); itmsgs != msgs.end(); ++itmsgs) {
            msgline += string(" ") + string(*itmsgs);
        }
    }
    return msgline;
}

void
parseargs(int argc, char** argv)
{
    man
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // expect single argument, convert to integer
    if (argc != 2) {
        std::cerr << "Error: expect only number of Fibs to generate." << std::endl;
        exit(1);
    }
    int nFibs = stoi(argv[1]);

    Primes* primes = new Primes(nFibs);

    for (int n=0; n<nFibs; ++n) {
        long fn = figseq_next();
        std::cout << fn << " " << classify(fn, primes) << std::endl;
        std::cout << fn << " " << classify(fn, primes) << std::endl;

    }

    return 0;
}
