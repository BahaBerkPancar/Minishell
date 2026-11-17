# Minishell

A small bash-like shell written in C, with an interactive prompt, pipes, redirections, heredocs, environment variables and built-in commands.

## What it does

- Interactive prompt (`MINISHELL : `) using GNU readline, with command history.
- Runs external programs found through `PATH` or given by path.
- Pipes (`cmd1 | cmd2 | ...`).
- Redirections: `<`, `>`, `>>` and heredoc `<<`.
- Single and double quotes, and `$VAR` expansion (including `$?` for the last exit status).
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Signals: Ctrl-C prints a fresh prompt, Ctrl-\ is ignored, Ctrl-D exits.
- Syntax errors print `SYNTAX ERROR` and set the exit status to 2.
- Not implemented: `&&`, `||`, wildcards, subshells.

## Build and run

```
make            # builds ./minishell (builds the bundled libft first)
make run        # builds and runs under valgrind with readline.supp
make clean      # removes objects
make fclean     # removes objects and the binary
make re         # fclean + all
make full-clean # fclean and also deletes libft/
```

Example:

```
./minishell
MINISHELL : echo hello | tr a-z A-Z > out.txt
MINISHELL : cat < out.txt
HELLO
```

Needs the readline library. On macOS install it with Homebrew (`brew install readline`); the Makefile picks it up automatically.

macOS note: the Makefile finds Homebrew readline with `brew --prefix readline` (falling back to `/opt/homebrew/opt/readline`) and passes its include path at compile time and its lib path at link time, so a plain `make` works. On Linux it just links `-lreadline`.

## How it works

Each line goes through four stages:

1. **Syntax check and tokenizing** (`parse/`): the line is split into a linked list of tokens, respecting single and double quotes.
2. **Typing and expansion** (`ext/type.c`, `env/`): each token gets a type (command, argument, flag, built-in, pipe, redirection, heredoc, and so on), `$VAR` and `$?` are expanded, and quotes are removed.
3. **Execution** (`execute/`): with no pipe, a lone built-in that changes shell state (`cd`, `export`, `unset`, `exit`) runs in the main process; anything else is forked. With pipes, one child is forked per command; each child connects its stdin and stdout to the neighbouring pipe ends with `dup2`, applies its own redirections, and then runs a built-in or calls `execve` on the resolved path. The parent waits for all children and stores the exit status.
4. **Heredocs** (`ext/heredoc.c`): a forked child reads lines with readline until the delimiter and writes them into a pipe; the read end becomes the command's standard input.

The environment lives in a `t_vault` struct (a copy of `envp`, plus separate `export` list, `pwd`, `oldpwd`), and a global `g_signal_exit` tells the SIGINT handler whether the shell is at the prompt, running a child or reading a heredoc.

## Project structure

- `minishell.c`, `signals.c`: main loop and signal handling
- `parse/`: tokenizer and quote handling
- `execute/`: pipes, forking, redirections, `execve`
- `built_ins/`: `echo`, `cd`, `pwd`, `export`, `unset`, `env`/`exit` dispatch
- `env/`: environment storage, variable expansion, PATH lookup
- `ext/`: helpers (token list, heredoc, freeing, checks)
- `include/`: headers
- `libft/`: bundled copy of my libft
- `readline.supp`: valgrind suppressions for readline

This is a 42 İstanbul project, written with a partner (the file headers list a second author).
