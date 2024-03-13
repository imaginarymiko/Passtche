#pragma once
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

const std::vector<std::string> CHARACTER_SETS = {
    "0123456789",
    "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~",
    " "
};

std::string getCharacterSet(const std::vector<bool>& options);

double calculateCombinations(const std::vector<bool>& options);

double calculateEntropy(const std::string& password, const std::vector<bool>& options);

int calculatePasswordLength(double entropy, const std::vector<bool>& options);
