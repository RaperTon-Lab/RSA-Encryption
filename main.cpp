#include "rsa.hpp"
#include "utils.hpp"
publicKey public_key;
cpp_int private_key;

void GenerateKeys()
{
    cpp_int first_prime, second_prime;
    first_prime = GetPrime();
    // std::cout << "First Prime " << first_prime << std::endl;
    second_prime = GetPrime();
    // std::cout << "SECOND Prime " << second_prime << std::endl;
    public_key = GeneratePublicKey(first_prime, second_prime);
    std::cout << std::endl
              << "public key " << public_key.public_key << std::endl
              << "\nexponent " << public_key.exponent << std::endl;
    private_key = GeneratePrivateKey(public_key.exponent);
    // std::cout << "\nPrivate key " << private_key << std::endl;
}
int main()
{

    // std::cout << PowerMod(4566, 123465, 6000);
    std::string str;
    cpp_int data;
    GenerateKeys();
    while (true)
    {
        std::cout << "\nEnter the data to be decrypted:\t";
        // std::getline(std::cin, str);
        // data = strToAscii(str);
        // std::cout << data << std::endl;
        // cpp_int encrypt_data = EncryptData(data, public_key);

        // std::cout << "\nThe encrypt data is " << encrypt_data << std::endl;
        //   std::cout << (public_key.public_key > encrypt_data) << std::endl;
        cpp_int encrypt_data;
        std::cin >> encrypt_data;
        cpp_int decrypt_data = DecryptData(encrypt_data, private_key, public_key.public_key);
        std::cout << "\nThe decrypted data is " << decrypt_data << std::endl;
        // std::string dec = asciiToStr(decrypt_data);
        std::cout << "\nThe decrypted data is " << decrypt_data << std::endl;
    }
}