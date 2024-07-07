#pragma once
#include <cmath>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#include "global.hh"

extern const std::vector<std::string> CHARACTER_SETS;

std::string getCharacterSet(const std::vector<bool>& options);

std::string generatePassword(size_t length, const std::string& characterSet);

double calculateCombinations(const std::vector<bool>& options);

double calculateEntropy(const std::string& password, const std::vector<bool>& options);

int calculatePasswordLength(double entropy, const std::vector<bool>& options);

std::string generateSalt();

std::string hashPassword(const std::string& password, const std::string& salt);

bool verifyPassword(const std::string& password, const std::string& salt, const std::string& storedHash);