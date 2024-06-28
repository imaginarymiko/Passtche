#include <iostream>
#include "inputparser.hh"
#include "generator.hh"

void printHelp() {
    std::cout << "Password Generator\n";
    std::cout << "Usage: \n";
    std::cout << "  password_generator <-h/-help>\n";
    std::cout << "  password-generator <-d/-digits> <-l/-lowercase> <-u/-uppercase> <-s/-special> <-S/-space> [-length length]\n";
    std::cout << "  password-generator <-d/-digits> <-l/-lowercase> <-u/-uppercase> <-s/-special> <-S/-space> [-entropy entropy]\n";
    std::cout << "\n";
    std::cout << "Options:\n";
    std::cout << "  -h, -help: Show this help message\n";
    std::cout << "  -d, -digits: Include digits in the character set\n";
    std::cout << "  -l, -lowercase: Include lowercase letters in the character set\n"; 
    std::cout << "  -u, -uppercase: Include uppercase letters in the character set\n";
    std::cout << "  -s, -special: Include special characters in the character set\n";
    std::cout << "  -S, -space: Include space in the character set\n";
    std::cout << "  -length length: Set length of the password to (length)\n";
    std::cout << "  -entropy entropy: Set entropy of the password to (entropy)\n";
    std::cout << "\n";
    std::cout << "Only one of -length or -entropy may be specified.\n";
    std::cout << "\n";
    std::cout << "Examples:\n";
    std::cout << "  password-generator -d -l -u -s -length 16\n";
    std::cout << "    Output: \n";
    std::cout << "Length: 16\nCharacter set size: 94\nEntropy: 283.565\nPassword: Xqtj~grXq}z&lfY<\n";
    std::cout << "  password-generator -d -l -entropy 128\n";
    std::cout << "    Output: \n";
    std::cout << "Length: 16\nCharacter set size: 36\nEntropy: 128.358\nPassword: 8q6x861mvu7e7ewj\n";
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    std::vector<std::string> validOptions = {"-h", "-help", "-d", "-digits", "-l", "-lowercase", "-u", "-uppercase", "-s", "-special", "-S", "-space", "-length", "-entropy"};
    int length = -1;
    int entropy = -1;
    std::vector<bool> options(5, false);
    bool useLength = true;
    try {
        InputParser input(argc, argv, validOptions);
        if (input.optionExists("-h") || input.optionExists("-help")) {
            printHelp();
            return 0;
        }
        if (input.optionExists("-d") || input.optionExists("-digits")) options[0] = true;
        if (input.optionExists("-l") || input.optionExists("-lowercase")) options[1] = true;
        if (input.optionExists("-u") || input.optionExists("-uppercase")) options[2] = true;
        if (input.optionExists("-s") || input.optionExists("-special")) options[3] = true;
        if (input.optionExists("-S") || input.optionExists("-space")) options[4] = true;
        if (input.optionExists("-length")) {
            std::string lengthStr = input.getOptionValue("-length");
            if (lengthStr.empty()) throw std::invalid_argument("Length option requires a value");
            length = std::stoi(lengthStr);
            if (length <= 0) throw std::invalid_argument("Length must be a positive integer");
        }
        if (input.optionExists("-entropy")) {
            useLength = false;
            std::string entropyStr = input.getOptionValue("-entropy");
            if (entropyStr.empty()) throw std::invalid_argument("Entropy option requires a value");
            entropy = std::stoi(entropyStr);
            if (entropy <= 0) throw std::invalid_argument("Entropy must be a positive integer");
        }
        if (length == -1 && entropy == -1) throw std::invalid_argument("Length or entropy option is required");
        if (length != -1 && entropy != -1) throw std::invalid_argument("Length and entropy options are mutually exclusive");
        if (useLength) {
            std::string characterSet = getCharacterSet(options);
            std::string password = generatePassword(length, characterSet);
            std::cout << "Length: " << length << std::endl;
            std::cout << "Character set size: " << characterSet.size() << std::endl;
            std::cout << "Entropy: " << calculateEntropy(password, options) << std::endl;
            std::cout << "Password: " << password << std::endl;
        } else {
            int passwordLength = calculatePasswordLength(entropy, options);
            std::string characterSet = getCharacterSet(options);
            std::string password = generatePassword(passwordLength, characterSet);
            std::cout << "Length: " << passwordLength << std::endl;
            std::cout << "Character set size: " << characterSet.size() << std::endl;
            std::cout << "Entropy: " << calculateEntropy(password, options) << std::endl;
            std::cout << "Password: " << password << std::endl;
        }
    } catch (std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return -1;
    }
    return 0;
}