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
#include <unistd.h>
#include <getopt.h>

using namespace std;

struct GlblArgs_t {
    bool verbose;               // be verbose, or not.
    int nFibs;                  // number of fibbonacci numbers
} glblargs;

static const char* optstr = "vh?"; // options string

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

    std::vector<long>::iterator it;
    long lastprime = primeslist.back();
    if (candidate <= lastprime) {
        for (it=primeslist.begin(); it != primeslist.end(); ++it)
            if (candidate == *it)
                return true;
    }
    long divisor;
    std::vector<long>::iterator itdiv;
    for (itdiv=primeslist.begin(); itdiv != primeslist.end(); ++itdiv) {
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
classify(long value, Primes* primes, bool verbose=false)
{
    vector <string> msgs;
    std::vector<string>::iterator itmsgs;

    primes->stretch(int(sqrt(value)));
    bool vv = verbose;

    if (value  % 5 == 0)            // divisible by 5
        msgs.push_back("Fizz" + string(vv?"5":""));
    if (value % 3 == 0)             // divisible by 3
        msgs.push_back("Buzz" + string(vv?"3":""));
    if (value % 15 == 0)            // divisible by 15
        msgs.push_back("FizzBuzz" + string(vv?"15":""));
    if (primes->isPrime(value))      // check for primeness
        msgs.push_back("BuzzFizz" + string(vv?"P":""));

    string msgline = "";
    if (msgs.size() != 0) {
        string first = *msgs.begin();
        msgline = string(first);
        msgs.erase(msgs.begin());
        for (itmsgs = msgs.begin(); itmsgs != msgs.end(); ++itmsgs) {
            msgline += string(" ") + string(*itmsgs);
        }
    } else {
        msgline = std::to_string(value);
    }
    return msgline;
}

void
displayUsage(void)
{
    printf( "ffbsolver - Fibonacci fizz buzz solver\n" );
    exit (EXIT_FAILURE);
}



int
main(int argc, char** argv) {

    int opt;
    extern char *optarg;
    extern int optind, optopt;

    glblargs.verbose = false;
    glblargs.nFibs = 0;

    while ((opt = getopt(argc, argv, optstr)) != -1) {
        switch (opt) {
          case 'v':
            glblargs.verbose = true;
            break;
          case 'h':
          case '?':
            displayUsage();
            break;
          default:
            /* can't get here */
            break;
        }
        opt = getopt( argc, argv, optstr);
    }
    for ( ; optind < argc; optind++) {
        glblargs.nFibs = stoi(argv[optind]);
    }

    Primes* primes = new Primes(glblargs.nFibs);

    for (int n=0; n<glblargs.nFibs; ++n) {
        long fn = figseq_next();
        if (glblargs.verbose)
            std::cout << fn << " " ;
        std::cout << classify(fn, primes, glblargs.verbose) << std::endl;
    }

    return 0;
}
