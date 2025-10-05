# 🐚 Minishell

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr)
[![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Grade](https://img.shields.io/badge/Grade-125%2F100-success)](https://profile.intra.42.fr/)

> *As beautiful as a shell* - A minimalist but complete Unix shell implementation

## 📖 Overview

A functional Unix shell built for 42 School that mimics bash behavior. The project implements command parsing, process management, redirections, pipes, and built-in commands while demonstrating deep understanding of system programming concepts.

**Key Learning Goals:**
- Unix shell internals and mechanics
- Process management and memory handling in C
- Complex input parsing and tokenization
- Inter-process communication and signals

## ✨ Features

### Core Functionality ✅
- **Interactive prompt** with working history
- **Command execution** with PATH resolution
- **Built-in commands**: `echo` (-n flag), `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Quote handling**: Single quotes (literal), Double quotes (variable expansion)
- **Redirections**: `<` `>` `<<` `>>` 
- **Pipes** (`|`) for command chaining
- **Environment variables** (`$VAR`) and exit status (`$?`)
- **Signal handling** (Ctrl-C, Ctrl-D, Ctrl-\\)

### Bonus Features 🎁
- Logical operators (`&&`, `||`) with parentheses
- Wildcards (`*`) for current directory

## 🚀 Installation

**Prerequisites:** GCC, Make, readline library
```bash
# Install readline (Ubuntu/Debian)
sudo apt-get install libreadline-dev

# Compile
make

# Run
./minishell
```

## 💡 Usage Examples

```bash
# Basic commands
./minishell
minishell$ ls -la
minishell$ /bin/echo "Hello World"
minishell$ pwd

# Built-ins and variables
minishell$ export MY_VAR=hello
minishell$ echo "Variable: $MY_VAR"
minishell$ echo '$USER'              # Prints literally: $USER
minishell$ echo "$USER"              # Expands variable

# Redirections and pipes
minishell$ echo "test" > file.txt
minishell$ cat file.txt | grep test
minishell$ cat << EOF
Hello
World
EOF

# Exit status
minishell$ ls /nonexistent
minishell$ echo $?                   # Shows error code
minishell$ exit 42
```

## 🏗 Project Structure

```
minishell/
├── src/
│   ├── builtins/          # Built-in commands (echo, cd, pwd, etc.)
│   ├── exec_init/         # Process execution and signal handling
│   ├── parsing/           # Input tokenization and parsing
│   ├── free_mem/          # Memory management
│   └── handle_env/        # Environment variable handling
├── include/               # Header files
├── libft/                # Custom C library
└── Makefile              # Build configuration
```

## 🧠 Key Concepts Learned

| **System Programming** | **Memory & Parsing** | **Unix Concepts** |
|----------------------|---------------------|------------------|
| Process management (`fork`, `execve`, `wait`) | Dynamic memory allocation | PATH resolution |
| File descriptors (`dup`, `pipe`) | String manipulation & tokenization | I/O redirection |
| Signal handling (`SIGINT`, `SIGQUIT`) | Data structures (linked lists) | Inter-process communication |
| Environment manipulation | Memory leak prevention | Process hierarchy |

## 🧪 Testing

```bash
# Compilation test
make -n                              # Verify compilation flags

# Basic functionality
echo "ls" | ./minishell             # Simple command
echo "echo 'test \$USER'" | ./minishell  # Quote handling
echo "ls | grep mini" | ./minishell      # Pipes

# Memory leak testing
make supp                           # Create Valgrind suppressions
valgrind --suppressions="$HOME/.supp.supp" ./minishell
```

## � Results

**Status:** ✅ Complete - Passes all mandatory evaluation tests  
**Grade:** 125/100 (with bonus)

The implementation successfully handles all required shell features including complex command parsing, proper memory management, and robust error handling.
