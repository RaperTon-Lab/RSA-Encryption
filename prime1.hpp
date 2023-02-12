#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_device.hpp>

using namespace boost::multiprecision;
// using namespace boost::random;

// Generate a secret RSA-like 512 bits primes p

cpp_int RangedRandomNumber(cpp_int min, cpp_int max)
{
    boost::mt19937 engine;
    typedef boost::uniform_int<cpp_int> NumberDistribution;
    typedef boost::mt19937 RandomNumberGenerator;
    typedef boost::variate_generator<RandomNumberGenerator &,
                                     NumberDistribution>
        Generator;

    NumberDistribution distribution(min, max);
    RandomNumberGenerator generator;
    Generator numberGenerator(generator, distribution);
    generator.seed(time(0));
    return numberGenerator();
}

cpp_int PowerMod(cpp_int x, cpp_int y, cpp_int p)
{
    cpp_int res = 1; // Initialize result
    x = x % p;       // Update x if it is more than or
                     // equal to p

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y / 2; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

cpp_int Power(cpp_int x, cpp_int y)
{
    cpp_int res = 1; // Initialize result
    x = x;           // Update x if it is more than or
                     // equal to p
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x);

        // y must be even now
        y = y / 2; // y = y/2
        x = (x * x);
    }
    return res;
}
cpp_int GetPrime()
{
    // boost::random::random_device rd;
    // boost::random::mt19937 rng(rd());
    /*boost::random::uniform_real_distribution<cpp_int> gen(0, 10000000000);*/
    boost::random::mt11213b base_gen(clock());
    boost::random::independent_bits_engine<boost::random::mt11213b, 2048, cpp_int> gen(base_gen);

    // Generate some large random primes
    // Note 25 trials of Miller-Rabin
    // likelihood that number is prime
    cpp_int n;
    do
    {
        n = gen();
    } while (!miller_rabin_test(n, 25));
    return n;
}
