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

```bash
Minishell > echo
Minishell >
```
(EXPECTED: \n)

```bash
Minishell > echo $NONEXIST
Minishell >
```
(EXPECTED: \n)

## Expand

```bash
Minishell > echo $$
$
```
(EXPECTED: pid(int))
leak si prochaine cmd == echo $NONEXIST

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

## Signals

ctrl \: errase prompt
(EXPECTED: ignore signal)

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
