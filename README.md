# 🐚 Minishell

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr)
[![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Grade](https://img.shields.io/badge/Grade-125%2F100-success)](https://profile.intra.42.fr/)

> *As beautiful as a shell* - Un'implementazione minimalista ma completa di una shell Unix

## 📚 Indice

- [Descrizione](#-descrizione)
- [Caratteristiche](#-caratteristiche)
- [Installazione](#-installazione)
- [Utilizzo](#-utilizzo)
- [Esempi](#-esempi)
- [Struttura del Progetto](#-struttura-del-progetto)
- [Concetti Appresi](#-concetti-appresi)
- [Test](#-test)
- [Autori](#-autori)

## 📖 Descrizione

Minishell è un progetto della 42 School che richiede l'implementazione di una shell Unix funzionale. Il progetto simula il comportamento di bash, includendo parsing dei comandi, gestione dei processi, redirezioni, pipes e built-in commands.

### Obiettivi del Progetto
- Comprendere il funzionamento interno di una shell Unix
- Imparare la gestione dei processi e della memoria in C
- Implementare parsing e tokenizzazione di input complessi
- Gestire segnali e comunicazione tra processi

## ✨ Caratteristiche

### Funzionalità Obbligatorie ✅
- **Prompt interattivo** con history funzionante
- **Esecuzione comandi** con ricerca nel PATH
- **Built-in commands**:
  - `echo` (con opzione -n)
  - `cd` (con path relativi/assoluti)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **Quotes handling**:
  - Single quotes (`'`) - nessuna interpretazione
  - Double quotes (`"`) - interpretazione variabili d'ambiente
- **Redirections**:
  - `<` input redirection
  - `>` output redirection  
  - `<<` here document
  - `>>` append mode
- **Pipes** (`|`) per concatenare comandi
- **Variabili d'ambiente** (`$VAR` expansion)
- **Exit status** (`$?`)
- **Gestione segnali** (Ctrl-C, Ctrl-D, Ctrl-\\)

### Funzionalità Bonus 🎁
- Logical operators (`&&`, `||`) con parentesi
- Wildcards (`*`) per directory corrente

## 🚀 Installazione

### Prerequisiti
- GCC compiler
- Make
- Libreria readline (`sudo apt-get install libreadline-dev` su Ubuntu)

### Compilazione
```bash
# Clone del repository
git clone [repository-url]
cd minishell

# Compilazione
make

# Pulizia file oggetto
make clean

# Pulizia completa
make fclean

# Ricompilazione completa
make re
```

## 🎯 Utilizzo

```bash
# Avvia minishell
./minishell

# La shell mostrerà il prompt:
minishell$ 
```

### Exit
```bash
# Esci dalla shell
exit
# oppure
exit [exit_code]
# oppure
Ctrl+D
```

## 💡 Esempi

### Comandi Base
```bash
minishell$ ls -la
minishell$ /bin/echo "Hello World"
minishell$ pwd
```

### Built-in Commands
```bash
minishell$ echo "Test message"
minishell$ echo -n "No newline"
minishell$ cd ../..
minishell$ pwd
minishell$ export MY_VAR=value
minishell$ env | grep MY_VAR
minishell$ unset MY_VAR
```

### Quotes e Variabili
```bash
minishell$ echo $USER
minishell$ echo '$USER'          # Stampa letteralmente $USER
minishell$ echo "$USER"          # Espande la variabile
minishell$ echo "Hello $USER!"   # Espansione in double quotes
```

### Redirections
```bash
minishell$ echo "Hello" > file.txt
minishell$ echo "World" >> file.txt
minishell$ cat < file.txt
minishell$ cat << EOF
> Hello
> World  
> EOF
```

### Pipes
```bash
minishell$ ls -la | grep minishell
minishell$ cat file.txt | grep Hello | wc -l
minishell$ echo "test" | cat | cat | cat
```

### Exit Status
```bash
minishell$ ls /nonexistent
minishell$ echo $?              # Stampa codice di errore
minishell$ echo "success"
minishell$ echo $?              # Stampa 0
```

## 🏗 Struttura del Progetto

```
minishell/
├── Makefile                    # Build configuration
├── README.md                   # Documentazione
├── include/                    # Header files
│   ├── builtin.h
│   ├── libft.h
│   ├── minishell.h
│   ├── parse_utils.h
│   └── struct.h
├── libft/                      # Libreria personale
│   └── src/
├── src/                        # Source code
│   ├── builtins/              # Built-in commands
│   │   ├── builtin.c
│   │   ├── ft_cd.c
│   │   ├── ft_echo.c
│   │   ├── ft_env.c
│   │   ├── ft_exit.c
│   │   ├── ft_pwd.c
│   │   ├── ft_unset.c
│   │   └── export/
│   ├── exec_init/             # Execution engine
│   │   ├── init_prompt.c
│   │   ├── minishell.c
│   │   ├── pipes.c
│   │   ├── process.c
│   │   ├── redir.c
│   │   ├── sig_handlers.c
│   │   └── utils.c
│   ├── free_mem/              # Memory management
│   ├── handle_env/            # Environment variables
│   └── parsing/               # Input parsing
│       └── input_management/
└── .build/                    # Compiled objects
```

## 🧠 Concetti Appresi

### Programmazione di Sistema
- **Gestione processi**: `fork()`, `execve()`, `wait()`, `waitpid()`
- **File descriptors**: `dup()`, `dup2()`, `pipe()`, `open()`, `close()`
- **Segnali**: `signal()`, `sigaction()`, gestione di SIGINT, SIGQUIT
- **Variabili d'ambiente**: `getenv()`, manipolazione environment

### Parsing e Tokenizzazione  
- **Lexical analysis**: tokenizzazione dell'input
- **Syntax parsing**: analisi grammaticale dei comandi
- **Quote handling**: gestione virgolette singole/doppie
- **Variable expansion**: espansione variabili d'ambiente

### Gestione Memoria
- **Dynamic allocation**: `malloc()`, `free()`, gestione leak
- **String manipulation**: parsing, splitting, joining
- **Data structures**: liste concatenate, strutture complesse

### Unix Shell Concepts
- **PATH resolution**: ricerca eseguibili nel PATH
- **I/O redirection**: gestione input/output streams  
- **Pipe communication**: comunicazione tra processi
- **Process hierarchy**: parent/child processes

### Architettura Software
- **Modular design**: separazione responsabilità
- **Error handling**: gestione errori robusta
- **Code organization**: strutturazione progetto

## 🧪 Test

Il progetto include una suite completa di test per verificare:

```bash
# Test compilazione
make -n                         # Verifica flags compilazione

# Test funzionalità base
echo "ls" | ./minishell        # Comando semplice
echo "" | ./minishell          # Comando vuoto
echo "   " | ./minishell       # Solo spazi

# Test built-ins
echo "pwd" | ./minishell
echo "echo hello" | ./minishell
echo "export TEST=value" | ./minishell

# Test quotes
echo "echo 'literal \$USER'" | ./minishell
echo 'echo "expanded $USER"' | ./minishell

# Test redirections
echo "echo hello > test.txt" | ./minishell
echo "cat < test.txt" | ./minishell

# Test pipes
echo "ls | grep mini" | ./minishell
```

### Memory Leaks
```bash
# Test con Valgrind (con suppressions per readline)
make supp
valgrind --suppressions="$HOME/.supp.supp" ./minishell

# Test base memory leaks
valgrind --leak-check=full ./minishell
```

## 👥 Autori

- **[Il Tuo Nome]** - *Sviluppo principale*
- **[Nome Partner]** - *Sviluppo collaborativo*

---

### 📈 Skills Sviluppate

| Categoria | Skills |
|-----------|---------|
| **System Programming** | Process management, File I/O, Signal handling |
| **Memory Management** | Dynamic allocation, Leak prevention, Data structures |
| **Parsing** | Tokenization, Grammar analysis, String processing |  
| **Unix Concepts** | Shell mechanics, Process communication, Environment |
| **Software Design** | Modular architecture, Error handling, Testing |

---

**Progetto completato con successo! ✅**

*Valutazione: 125/100 (con bonus)*