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

std::string generatePassword(size_t length, const std::string& characterSet) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characterSet.size() - 1);
    std::string password = "";
    for (int i = 0; i < length; ++i) password += characterSet[dis(gen)];
    return password;
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

std::string generateSalt() {
    unsigned char salt[SALT_SIZE];
    RAND_bytes(salt, SALT_SIZE);
    return std::string(reinterpret_cast<char*>(salt), SALT_SIZE);
}

std::string hashPassword(const std::string& password, const std::string& salt) {
    unsigned char key[AES_KEY_SIZE];
    PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), password.length(), 
                           reinterpret_cast<const unsigned char*>(salt.c_str()), 
                           salt.length(), 10000, AES_KEY_SIZE, key);
    return std::string(reinterpret_cast<char*>(key), AES_KEY_SIZE);
}

bool verifyPassword(const std::string& password, const std::string& salt, const std::string& storedHash) {
    std::string keyHash = hashPassword(password, salt);
    return keyHash == storedHash;
}
