#pragma once
#include <string>
#include <vector>

#define AES_KEY_SIZE 32
#define SALT_SIZE 16

const std::vector<std::string> CHARACTER_SETS = {
    "0123456789",
    "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~",
    " "
};
