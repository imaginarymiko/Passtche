#include "generator.hh"

std::string generatePassword(int length, const std::string& characterSet) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characterSet.size() - 1);
    std::string password = "";
    for (int i = 0; i < length; ++i) {
        password += characterSet[dis(gen)];
    }
    return password;
}
