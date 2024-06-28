#include "pwutils.hh"

std::string getCharacterSet(const std::vector<bool>& options) {
    std::string characterSet = "";
    if (options[0]) characterSet += CHARACTER_SETS[0];
    if (options[1]) characterSet += CHARACTER_SETS[1];
    if (options[2]) characterSet += CHARACTER_SETS[2];
    if (options[3]) characterSet += CHARACTER_SETS[3];
    if (options[4]) characterSet += CHARACTER_SETS[4];
    return characterSet;
}

double calculateCombinations(const std::vector<bool>& options) {
    double combinations = 1;
    for (int i = 0; i < options.size(); ++i) if (options[i]) combinations *= CHARACTER_SETS[i].size();
    return combinations;
}

double calculateEntropy(const std::string& password, const std::vector<bool>& options) {
    return std::log2(calculateCombinations(options)) * password.size();
}

int calculatePasswordLength(double entropy, const std::vector<bool>& options) {
    return std::ceil(entropy / std::log2(calculateCombinations(options)));
}
