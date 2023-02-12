#pragma once
#include "prime1.hpp"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>

using bigInt = boost::multiprecision::cpp_int;

using bigFloat = boost::multiprecision::cpp_dec_float_100;

bigInt euler_totem_var;

class publicKey
{
public:
    bigInt public_key;
    bigInt exponent;
};

void EulerTotient(bigInt first_prime, bigInt second_prime)
{
    euler_totem_var = (first_prime - 1) * (second_prime - 1);
}

bigInt gcd(bigInt a, bigInt b)
{
    /* GCD(0, b) == b; GCD(a, 0) == a,
       GCD(0, 0) == 0 */
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    /*Finding K, where K is the
      greatest power of 2
      that divides both a and b. */
    bigInt k;
    for (k = 0; ((a | b) & 1) == 0; ++k)
    {
        a >>= 1;
        b >>= 1;
    }

    /* Dividing a by 2 until a becomes odd */
    while ((a & 1) == 0)
        a >>= 1;

    /* From here on, 'a' is always odd. */
    do
    {
        /* If b is even, remove all factor of 2 in b */
        while ((b & 1) == 0)
            b >>= 1;

        /* Now a and b are both odd.
           Swap if necessary so a <= b,
           then set b = b - a (which is even).*/
        if (a > b)
            swap(a, b); // Swap u and v.

        b = (b - a);
    } while (b != 0);

    /* restore common factors of 2 */
    return a * Power(2, k);
}

publicKey GeneratePublicKey(bigInt first_prime, bigInt second_prime)
{
    publicKey public_key;
    bigInt first_part_public_key = first_prime * second_prime;
    EulerTotient(first_prime, second_prime);
    bigInt e = 1;
    while (e < euler_totem_var)
    {
        if (miller_rabin_test(e, 25))
            if (gcd(euler_totem_var, e) == 1)
                break;
        e = RangedRandomNumber(1000, 100000);
    }
    public_key.public_key = first_part_public_key;
    public_key.exponent = e;
    return public_key;
}

bigInt GeneratePrivateKey(bigInt exponent)
{
    bigInt private_key;
    bigInt a[2], b[2], d[2];
    bigInt k[2];
    a[0] = 1;
    b[0] = 0;
    d[0] = euler_totem_var;
    k[0] = -1;
    a[1] = 0;
    b[1] = 1;
    d[1] = exponent;
    k[1] = euler_totem_var / exponent;

    bigInt ai, bi, di;
    bigInt ki;
    while (d[1] != 1)
    {

        ai = a[0] - (a[1] * k[1]);
        bi = b[0] - (b[1] * k[1]);
        di = d[0] - (d[1] * k[1]);

        ki = d[1] / di;
        a[0] = a[1];
        b[0] = b[1];
        d[0] = d[1];
        k[0] = k[1];
        a[1] = ai;
        b[1] = bi;
        d[1] = di;
        k[1] = ki;
    }
    private_key = b[1];
    if (private_key > euler_totem_var)
        private_key = private_key % euler_totem_var;
    if (private_key < 0)
        private_key += euler_totem_var;

    return private_key;
}

bigInt EncryptData(bigInt data, publicKey public_key)
{

    bigInt encrypted_data = PowerMod(data, public_key.exponent, public_key.public_key);
    return encrypted_data;
}

bigInt DecryptData(bigInt encrypt_data, bigInt private_key, bigInt public_key)
{
    bigInt decrypted_data = PowerMod(encrypt_data, private_key, public_key);
    return decrypted_data;
}