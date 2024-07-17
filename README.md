Minishell Project README
Table of Contents

    Introduction
    Features
    Installation
    Usage
    Commands

Introduction

Minishell is a lightweight shell designed to provide essential command-line interface functionality. It serves as an educational, simplified version of Unix shells like bash or zsh, created to help users understand shell operations, process management, and user input handling.
Features

    Execution of basic commands (e.g., ls, echo, pwd)
    Support for built-in shell commands (cd, echo, exit, export, pwd, unset)
    Input and output redirection (>, <, >>, <<)
    Command pipelining using |
    Environment variable management and expansion
    Signal handling (e.g., Ctrl+C to interrupt a running command and Ctrl+D)

Installation

To install and set up Minishell, follow these instructions:

    Clone the repository:

    sh

git clone https://github.com/yourusername/minishell.git
cd minishell

Compile the project:

sh

    make m

    This command compiles the source code and produces the minishell executable.

Usage

To begin using Minishell, enter the following command in your terminal:

sh

./minishell

You will see a prompt where you can start entering commands.
Commands

Minishell supports various commands, including built-in commands and external commands available in your system's PATH.
Built-in Commands

    cd [directory]: Change the current directory to the specified directory.
        cd ..: Navigate to the parent directory.
        cd ~: Navigate to the home directory.
        cd .: Remain in the current directory.

    exit [status]: Exit the shell with an optional exit status code.

    echo [string]: Display string in the terminal.
        echo -n [string]: Display string without a trailing newline.

    env: Display all environment variables.

    export [var]=[value]: Assign the value value to the environment variable var.

    unset [var]: Remove the environment variable var.

External Commands

Any executable located in the directories listed in the PATH environment variable can be executed. For example:

sh

ls -la
grep "pattern" file.txt

Redirection

    Output Redirection: Use > to direct output to a file.

    sh

echo "Hello, World!" > hello.txt

Append Output Redirection: Use >> to append output to an existing file.

sh

echo "Hello, again!" >> hello.txt

Input Redirection: Use < to read input from a file.

sh

cat < hello.txt

Here Document: Use << to take input from a string until a specified delimiter is encountered.

sh

    cat << EOF
    Hello, World!
    EOF

Pipelining

Use | to send the output of one command as input to another.

sh

ls -la | grep "pattern"

This Minishell project is part of the 42 Berlin curriculum.

„Non scholae sed vitae discimus.“
