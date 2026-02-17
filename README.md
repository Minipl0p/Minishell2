*This project has been created as part of the 42 curriculum by pchazalm, pcaplat.*

------------------------------------------------------------------------

# Minishell

## Description

**Minishell** is a simplified UNIX shell reimplementation written in C,
developed as part of the 42 School curriculum.

The goal of this project is to deeply understand:

-   Process creation and management
-   File descriptors and redirections
-   Pipes and inter-process communication
-   Signals handling
-   Environment variable management
-   Parsing and lexical analysis
-   Terminal behavior and user interaction

Minishell reproduces the core behavior of **bash**, including command
execution, pipelines, redirections, environment variable expansion, and
built-in commands.

### Mandatory Features

-   Prompt display
-   Command history
-   Execution of binaries (via `PATH`)
-   Environment variable expansion (`$VAR`)
-   Exit status expansion (`$?`)
-   Pipes (`|`)
-   Redirections:
    -   Input `<`
    -   Output `>`
    -   Append `>>`
    -   Heredoc `<<`
-   Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
-   Builtins:
    -   `echo`
    -   `cd`
    -   `pwd`
    -   `export`
    -   `unset`
    -   `env`
    -   `exit`

### Bonus Features

-   Logical operators (`&&`, `||`)
-   Parentheses for priority handling
-   Wildcards (`*`)
-   Advanced signal behavior matching bash more precisely

------------------------------------------------------------------------

## Instructions

### Requirements

-   Unix-based system (Linux recommended)
-   `gcc`
-   `make`
-   GNU Readline library

### Compilation

To compile the project:

``` bash
make
```

To clean object files:

``` bash
make clean
```

To remove all the generated files:

``` bash
make fclean
```

To recompile the project:

``` bash
make re
```

### Execution

``` bash
./minishell
```

To exit:

``` bash
exit
```

or press `Ctrl-D`.

------------------------------------------------------------------------

## Examples

### Basic Command

``` bash
minishell$ ls -l
```

### Environment Variable Expansion

``` bash
minishell$ echo $HOME
```

### Exit Status

``` bash
minishell$ ls file_that_does_not_exist
minishell$ echo $?
```

### Redirections

``` bash
minishell$ echo "Hello World" > file.txt
minishell$ cat < file.txt
```

### Pipes

``` bash
minishell$ ls | grep minishell
```

### Heredoc

``` bash
minishell$ cat << EOF
> Hello
> World
> EOF
```

------------------------------------------------------------------------

## Bonus Examples

``` bash
minishell$ make && echo "Compilation succeeded"
```

``` bash
minishell$ make || echo "Compilation failed"
```

``` bash
minishell$ (echo Hello && echo World) || echo Error
```

``` bash
minishell$ ls *.c
```

------------------------------------------------------------------------

## Resources

### GNU Documentation

-   GNU C Library documentation
-   GNU Readline documentation
-   GNU man pages
-   Bash Reference Manual

### Reference Shell

Throughout the project, **GNU Bash** was used as the behavioral
reference.

------------------------------------------------------------------------

## Final Notes

Minishell is a deep dive into UNIX system programming and shell
internals.
It strengthens knowledge in process control, memory management, parsing,
and debugging complex execution flows.
