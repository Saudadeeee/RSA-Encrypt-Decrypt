#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
 
using namespace std;
 
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 
long long modExp(long long a, long long b, long long n) {
    long long result = 1;
    a = a % n; 
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % n;
        }
        b = b >> 1;
        a = (a * a) % n;
    }
    return result;
}
 
long long modInverse(long long a, long long m) {
    long long m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
 
    while (a > 1) {
    while (a > 1) {
        long long q = a / m;
        long long t = m;
 
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
 
    if (x < 0) x += m0;
 
    return x;
}
 
bool isPrime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}
 
long long generateRandomPrime() {
    long long prime;
    do {
        prime = rand() % 90000 + 10000; // Random number between 10000 and 99999
    } while (!isPrime(prime));
    return prime;
}
 
void generateKeys(long long &n, long long &e, long long &d) {
    srand(time(0));
    long long p = generateRandomPrime();  
    long long q = generateRandomPrime();  
    n = p * q;       
    long long phi = (p - 1) * (q - 1);  
 
    do {
        e = rand() % (phi - 2) + 2; // Random number between 2 and phi-1
    } while (gcd(e, phi) != 1);
 
    d = modInverse(e, phi);
}
 
// RSA Encryption
long long encrypt(long long message, long long e, long long n) {
    return modExp(message, e, n);
}
 
// RSA Decryption
long long decrypt(long long ciphertext, long long d, long long n) {
    return modExp(ciphertext, d, n);
}
 
vector<long long> encryptText(const string &message, long long e, long long n) {
    vector<long long> encryptedMessage;
    for (char ch : message) {
        long long encryptedChar = encrypt(static_cast<long long>(ch), e, n);
        encryptedMessage.push_back(encryptedChar);
    }
    return encryptedMessage;
}
 
string decryptText(const vector<long long> &encryptedMessage, long long d, long long n) {
    string decryptedMessage;
    for (long long ch : encryptedMessage) {
        long long decryptedChar = decrypt(ch, d, n);
        decryptedMessage.push_back(static_cast<char>(decryptedChar));
    }
    return decryptedMessage;
}
 
int main() {
    // Key Generation
    long long n, e, d;
    generateKeys(n, e, d);
    cout << "Public Key (n, e): (" << n << ", " << e << ")\n";
    cout << "Private Key (n, d): (" << n << ", " << d << ")\n";
    string message;
    cout << "Enter the text message to be encrypted: ";
    getline(cin, message);
 
    // Encryption
    vector<long long> encrypted = encryptText(message, e, n);
    cout << "Encrypted Message: ";
    for (long long ch : encrypted) {
        cout << ch << " ";
    }
    cout << "\n";
 
    // Decryption
    string decrypted = decryptText(encrypted, d, n);
    cout << "Decrypted Message: " << decrypted << "\n";
 
    return 0;
}