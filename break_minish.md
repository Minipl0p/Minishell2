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

## BONUS

```bash
Minishell > true || echo a && echo b
Minishell >
```
(EXPECTED: b)

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

## Lexer

```bash
Minishell > echo a"b

```
(LOOP)

syntaxe error on set_word_len

## shlag

probleme emoji fail readline
EXIT
doublons destroy.c && ast_tools.c

