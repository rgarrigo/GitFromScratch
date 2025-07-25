# Custom git

## Build
To build the exercise exXX:
```EXO=exXX make```
It will build everything using the params.h file in include/exXX/

## Description
The program compiled is a restriction of the /usr/bin/git program

Each params.h contains two parameters:
- An array containing all the subcommands that can be launched
- A path to an executable that will be launched if the program succeed

A subcommand consists of:
- Its name
- Its description
- Its options

An option consists of
- Its name
- Its description

Each name is the string that should be used during the CLI call
```git <subcommand-name> <subcommand-option-name> <arguments>```
Each description is printed during a call to 'git --help' or equivalent to describe the subcommand or option

## Licensing
Copyright (C) 2025 rgarrigo
This code is licensed under the GPLv3 License
See the LICENSE file for more details
