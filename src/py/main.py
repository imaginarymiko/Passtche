#!/usr/bin/env python3
import sys
from typing import List
from pwutils import *

def print_help() -> None:
    print("Password Generator")
    print("Usage:")
    print("  password_generator <-h/-help>")
    print("  password_generator [-d/-digits] [-l/-lowercase] [-u/-uppercase] [-s/-special] [-S/-space] <-length length>")
    print("  password_generator [-d/-digits] [-l/-lowercase] [-u/-uppercase] [-s/-special] [-S/-space] <-entropy entropy>")
    print("")
    print("Options:")
    print("  -h, -help: Show this help message")
    print("  -d, -digits: Include digits in the character set")
    print("  -l, -lowercase: Include lowercase letters in the character set") 
    print("  -u, -uppercase: Include uppercase letters in the character set")
    print("  -s, -special: Include special characters in the character set")
    print("  -S, -space: Include space in the character set")
    print("  -length length: Set length of the password to (length)")
    print("  -entropy entropy: Set entropy of the password to (entropy)")
    print("")
    print("Only one of -length or -entropy may be specified.")
    print("")
    print("Examples:")
    print("  password-generator -d -l -u -s -length 16")
    print("    Output:") 
    print("Length: 16")
    print("Character set size: 94")
    print("Entropy: 283.565")
    print("Password: Xqtj~grXq}z&lfY<")
    print("  password-generator -d -l -entropy 128")
    print("    Output:")
    print("Length: 16")
    print("Character set size: 36")
    print("Entropy: 128.358")
    print("Password: 8q6x861mvu7e7ewj")

if __name__ == "__main__":
    valid_options: List[str] = ["-h", "-help", "-d", "-digits", "-l", "-lowercase", "-u", "-uppercase", "-s", "-special", "-S", "-space", "-length", "-entropy"]
    length: int = -1
    entropy: int = -1
    options: List[bool] = [False] * 5
    use_length: bool = True

    try:
        if "-h" in sys.argv or "-help" in sys.argv:
            print_help()
            sys.exit(0)

        for i, arg in enumerate(sys.argv[1:-1]):
            if arg not in valid_options:
                raise ValueError(f"Invalid option: {arg}")
            if arg == "-length":
                length = int(sys.argv[i + 2])
                use_length = True
            elif arg == "-entropy":
                entropy = int(sys.argv[i + 2])
                use_length = False
            elif arg in ["-d", "-digits"]:
                options[0] = True
            elif arg in ["-l", "-lowercase"]:
                options[1] = True
            elif arg in ["-u", "-uppercase"]:
                options[2] = True
            elif arg in ["-s", "-special"]:
                options[3] = True
            elif arg in ["-S", "-space"]:
                options[4] = True

        if length == -1 and entropy == -1:
            raise ValueError("Length or entropy option is required")
        if length != -1 and entropy != -1:
            raise ValueError("Length and entropy options are mutually exclusive")

        character_set: str = get_character_set(options)

        if use_length:
            password: str = generate_password(length, character_set)
            print(f"Length: {length}")
            print(f"Character set size: {len(character_set)}")
            print(f"Entropy: {calculate_entropy(password, options)}")
            print(f"Password: {password}")
        else:
            password_length: int = calculate_password_length(entropy, options)
            password: str = generate_password(password_length, character_set)
            print(f"Length: {password_length}")
            print(f"Character set size: {len(character_set)}")
            print(f"Entropy: {calculate_entropy(password, options)}")
            print(f"Password: {password}")

    except (ValueError, IndexError) as e:
        print(f"Error: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Unknown error: {e}")
        sys.exit(-1)