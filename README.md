# Password Generator

## Overview:
This program generates secure passwords based on specified criteria such as length or entropy. It allows users to customise the character set used in password generation.

## Usage:
`password-generator <-h/-help>`<br>
`password-generator <-d/-digits> <-l/-lowercase> <-u/-uppercase> <-s/-special> <-S/-space> [-length length]`<br>
`password-generator <-d/-digits> <-l/-lowercase> <-u/-uppercase> <-s/-special> <-S/-space> [-entropy entropy]`<br>
* `-h`, `-help`: Show the help message.
* `-d`, `-digits`: Include digits in the character set.
* `-l`, `-lowercase`: Include lowercase letters in the character set.
* `-u`, `-uppercase`: Include uppercase letters in the character set.
* `-s`, `-special`: Include special characters in the character set.
* `-S`, `-space`: Include space in the character set.
* `-length length`: Set the length of the password to `length`.
* `-entropy entropy`: Set the entropy of the password to `entropy`.

Only one of `-length` or `-entropy` may be specified.

## Examples:
`password-generator -d -l -u -s -length 16`<br>
Output:
```
Length: 16
Character set size: 94
Entropy: 283.565
Password: Xqtj~grXq}z&lfY<
```
`password-generator -d -l -entropy 128`<br>
Output:
```
Length: 16
Character set size: 36
Entropy: 128.358
Password: 8q6x861mvu7e7ewj
```