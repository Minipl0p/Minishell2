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

## shlag

probleme emoji fail readline
EXIT

