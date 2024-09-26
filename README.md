# Minishell README

Minishell is a lightweight shell designed to provide essential command-line interface functionality. It serves as an educational, simplified version of Unix shells like bash or zsh, created to help users understand shell operations, process management, and user input handling.
Features

## Table of Contents

    Features
    Installation
    Usage

### Features

    Execution of basic commands (e.g., ls, echo, pwd)
    Support for built-in shell commands (cd, echo, exit, export, pwd, unset)
    Input and output redirection (>, <, >>, <<)
    Command pipelining using |
    Environment variable management and expansion
    Signal handling (e.g., Ctrl+C to interrupt a running command and Ctrl+D)

## Installation

To install and set up Minishell, follow these instructions:

    Clone the repository:
    git clone https://github.com/yourusername/minishell.git
    cd minishell
    Compile the project:
    make m

## Usage

### Start
To begin using Minishell, enter the following command in your terminal:

    ./minishell

You will see a prompt where you can start entering commands.

Minishell supports various commands, including:

### Built-in Commands

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

### External Commands

Any executable located in the directories listed in the PATH environment variable can be executed. For example:

    ls -la
    grep "pattern" file.txt
    Output Redirection: Use > to direct output to a file.
    Append Output Redirection: Use >> to append output to an existing file.
    echo "Hello, World!" > hello.txt
    echo "Hello, again!" >> hello.txt
    Input Redirection: Use < to read input from a file.
    cat < hello.txt
    Here Document: Use << to take input from a string until a specified delimiter is encountered.
    cat << EOF
    Hello, World!
    EOF
    Use | to send the output of one command as input to another.
    ls -la | grep "pattern"

This Minishell project is part of the 42 Berlin curriculum.

„Non scholae sed vitae discimus.“
