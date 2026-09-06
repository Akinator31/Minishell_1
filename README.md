# Minishell1

UNIX command interpreter written in C, developed as part of the Epitech curriculum. This project is a first approach to shell mechanics and serves as an introduction before the 42sh project.

## Description

Minishell1 (binary `mysh`) reproduces the basic behavior of a TCSH-inspired shell: it displays a prompt, reads a command line, executes it, then displays the prompt again. Only simple commands are supported, without pipes or redirections.

Commands are looked up in the directories listed in the `PATH` environment variable, or executed directly if a path is provided (for example `./my_program`).

## Features

- Dynamic prompt displaying the hostname and current directory
- Reading and execution of simple commands
- Command resolution via `PATH` or via a direct path
- Environment copied at startup and restored to its initial state
- Shell exit code identical to the exit code of the last executed command
- Same behavior in interactive mode and non-interactive mode (redirected input, for example via `echo "command" | ./mysh`)
- Error handling on standard error, with exit code 84 on internal errors

## Builtins

| Command | Description |
|---|---|
| `cd [directory]` | Changes the current directory. Without argument, moves to `HOME`. Also supports `~` and `-` |
| `env` | Prints the current environment variables, no argument |
| `setenv [name] [value]` | Creates or updates an environment variable |
| `unsetenv name` | Removes an environment variable (the `*` wildcard is not supported) |
| `exit` | Exits the shell |

## Compilation

The project is built with `make`, using a Makefile that provides the following rules:

```bash
make            # builds the mysh binary
make debug      # builds a debug version with AddressSanitizer
make tests_run  # builds and runs the unit tests (Criterion)
make show_test  # runs the tests and generates an HTML coverage report
make clean      # removes object files
make fclean     # removes object files, binaries and generated reports
make re         # fclean then full rebuild
```

## Usage

Interactive mode:

```bash
./mysh
$> pwd
/home/user
$> cd Documents
$> pwd
/home/user/Documents
```

Non-interactive mode:

```bash
echo "ls -l" | ./mysh
```

The shell exits with `exit`, or with `EOF` (Ctrl+D) in interactive mode.

## Exit codes

The shell returns the exit code of the last executed command. When there is no error, the exit code is 0. On an internal error (command not found, invalid argument, builtin error), the exit code is 84.

## Project structure

```
.
├── include/        project headers
├── lib/            reimplemented basic utility functions
├── src/
│   ├── commands/   builtins and execution of external commands
│   ├── utils/      command parsing, environment handling, prompt
│   └── main.c      program entry point
├── tests/          unit tests (Criterion)
└── Makefile
```

## Project constraints

As required by the Epitech subject, only the following functions are allowed: `malloc`, `free`, `exit`, `opendir`, `readdir`, `closedir`, `getcwd`, `chdir`, `fork`, `stat`, `lstat`, `fstat`, `open`, `close`, `getline`, `strtok`, `strtok_r`, `read`, `write`, `execve`, `access`, `isatty`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `kill`, `getpid`, `strerror`, `perror`, `strsignal`.

Pipes, redirections and other advanced shell features are not supported in this project.

## Tests

Unit tests are written with Criterion and located in the `tests/` directory. They can be run with `make tests_run`, and a coverage report can be generated with `make show_test`.
