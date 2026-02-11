# Minishell Edge Cases

## Echo

```bash
Minishell > echo ""
"
Minishell >
```
Expected : \n !

```bash
Minishell > echo ''
'
```
(EXPECTED: \n)

## Syntax

```bash
Minishell > echo "hello
Minishell >
```
(EXPECTED: syntaxe error)

```bash
Minishell > | ls
Minishell: sytaxe error:...
Includes src main.c ...
```
(EXPECTED: sytaxe error and no exec)

## BONUS

```bash
Minishell > true || echo a && echo b
Minishell >
```
(EXPECTED: b)

```bash
Minishell > ((echo a))
a
```
(EXPECTED: syntax error)


### WILDCARDS

```bash
Minishell > echo *
```
LEAKS

```bash
Minishell > echo *.c
```
LEAKS

```bash
Minishell > echo *sjdfhgsd
```
LEAKS


## shlag

probleme emoji fail readline
EXIT
