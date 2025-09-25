# 🐚 Minishell - 42 School Project

A simple shell implementation in C that replicates basic functionality of bash, built as part of the 42 School curriculum.

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Implementation Details](#implementation-details)
- [Project Structure](#project-structure)
- [Key Concepts](#key-concepts)
- [Testing](#testing)
- [Known Limitations](#known-limitations)
- [Authors](#authors)

## 🎯 About

Minishell is a project that challenges students to create their own shell, similar to bash. This project teaches fundamental concepts of:
- **Process management** and system calls
- **Signal handling** and process control
- **Memory management** and error handling
- **Parsing** and lexical analysis
- **Environment variables** and shell behavior

## ✨ Features

### Core Functionality
- ✅ **Command execution** with absolute and relative paths
- ✅ **Built-in commands** (echo, cd, pwd, export, unset, env, exit)
- ✅ **Environment variables** expansion (`$VAR`, `$?`)
- ✅ **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\)
- ✅ **Command history** navigation
- ✅ **Prompt display** with shell name

### Advanced Features
- ✅ **Pipes** (`|`) for command chaining
- ✅ **Redirections** (`<`, `>`, `>>`, `<<`)
- ✅ **Here documents** (`<<`) with delimiter
- ✅ **Quote handling** (single `'` and double `"` quotes)
- ✅ **Logical operators** (`&&`, `||`)
- ✅ **Wildcards** (`*`) for filename expansion
- ✅ **Subshells** and command substitution

## 🚀 Installation

\`\`\`bash
# Clone the repository
git clone <your-repo-url>
cd minishell

# Compile the project
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile everything
make re
\`\`\`

### Dependencies
- **readline library** for command line editing
- **GNU Make** for compilation
- **GCC** compiler

## 💻 Usage

\`\`\`bash
# Start the shell
./minishell

# You'll see the prompt
minishell$ 
\`\`\`

### Basic Commands
\`\`\`bash
# Execute simple commands
minishell$ ls -la
minishell$ pwd
minishell$ echo "Hello World"

# Use pipes
minishell$ ls | grep .c | wc -l

# Redirections
minishell$ echo "test" > file.txt
minishell$ cat < file.txt
minishell$ ls >> output.txt

# Environment variables
minishell$ echo $HOME
minishell$ export MY_VAR="Hello"
minishell$ echo $MY_VAR

# Exit the shell
minishell$ exit
\`\`\`

## 🔧 Built-in Commands

| Command | Description | Usage |
|---------|-------------|-------|
| `echo` | Display text with optional `-n` flag | `echo [-n] [text...]` |
| `cd` | Change directory | `cd [directory]` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variables | `export [VAR=value]` |
| `unset` | Unset environment variables | `unset [VAR]` |
| `env` | Display environment variables | `env` |
| `exit` | Exit the shell | `exit [status]` |

### Built-in Command Details

#### echo
\`\`\`bash
minishell$ echo Hello World
Hello World
minishell$ echo -n "No newline"
No newline minishell$ 
\`\`\`

#### cd
\`\`\`bash
minishell$ cd /home/user
minishell$ cd ..
minishell$ cd ~
minishell$ cd -  # Go to previous directory
\`\`\`

#### export/unset
\`\`\`bash
minishell$ export PATH="/usr/bin:$PATH"
minishell$ export MY_VAR="test"
minishell$ unset MY_VAR
\`\`\`

## 🏗️ Implementation Details

### Core Components

#### Lexer/Tokenizer
- Breaks input into tokens (commands, arguments, operators)
- Handles quotes and escape characters
- Recognizes special characters (`|`, `<`, `>`, etc.)

#### Parser
- Builds command structures from tokens
- Handles operator precedence
- Creates execution trees for complex commands

#### Executor
- Manages process creation and execution
- Handles pipes and redirections
- Implements built-in commands

#### Signal Handler
- `SIGINT` (Ctrl+C): Interrupt current command
- `SIGQUIT` (Ctrl+\): Ignored in interactive mode
- `EOF` (Ctrl+D): Exit shell gracefully

### Data Structures

\`\`\`c
typedef struct s_token {
    char            *value;
    int             type;
    struct s_token  *next;
} t_token;

typedef struct s_cmd {
    char            **args;
    char            *input_file;
    char            *output_file;
    int             append_mode;
    int             here_doc;
    struct s_cmd    *next;
} t_cmd;

typedef struct s_shell {
    char            **env;
    char            *prompt;
    int             exit_status;
    t_cmd           *commands;
} t_shell;
\`\`\`

## 📁 Project Structure

\`\`\`
minishell/
├── Makefile              # Build configuration
├── includes/
│   └── minishell.h      # Header file with structures and prototypes
├── src/
│   ├── main.c           # Main program entry point
│   ├── lexer/
│   │   ├── tokenizer.c  # Input tokenization
│   │   └── quotes.c     # Quote handling
│   ├── parser/
│   │   ├── parser.c     # Command parsing
│   │   └── expansion.c  # Variable expansion
│   ├── executor/
│   │   ├── executor.c   # Command execution
│   │   ├── pipes.c      # Pipe handling
│   │   └── redirections.c # Redirection handling
│   ├── builtins/
│   │   ├── echo.c       # Echo command
│   │   ├── cd.c         # Change directory
│   │   ├── pwd.c        # Print working directory
│   │   ├── export.c     # Export variables
│   │   ├── unset.c      # Unset variables
│   │   ├── env.c        # Environment display
│   │   └── exit.c       # Exit command
│   ├── signals/
│   │   └── signals.c    # Signal handling
│   └── utils/
│       ├── utils.c      # Utility functions
│       ├── memory.c     # Memory management
│       └── error.c      # Error handling
└── README.md            # This file
\`\`\`

## 🧠 Key Concepts

### Process Management
- **Fork/Exec**: Creating child processes for command execution
- **Wait**: Parent process waiting for child completion
- **Process groups**: Managing related processes

### File Descriptors
- **Standard streams**: stdin (0), stdout (1), stderr (2)
- **Pipe creation**: Using `pipe()` system call
- **Redirection**: Using `dup2()` to redirect file descriptors

### Memory Management
- **Dynamic allocation**: Using malloc/free for flexible data structures
- **Memory leaks**: Proper cleanup of allocated memory
- **String manipulation**: Safe string operations

### Signal Handling
\`\`\`c
// Example signal handler setup
signal(SIGINT, handle_sigint);
signal(SIGQUIT, SIG_IGN);
\`\`\`

## 🧪 Testing

### Basic Functionality Tests
\`\`\`bash
# Simple commands
echo "test"
ls -la
pwd

# Built-ins
cd /tmp
export TEST="value"
echo $TEST
unset TEST
env | grep TEST
exit 0
\`\`\`

### Advanced Feature Tests
\`\`\`bash
# Pipes
ls | grep .c | wc -l
cat file.txt | head -5 | tail -2

# Redirections
echo "test" > output.txt
cat < input.txt > output.txt
ls >> log.txt

# Here documents
cat << EOF
This is a here document
Multiple lines supported
EOF

# Quotes and variables
echo "Hello $USER"
echo 'Literal $USER'
echo "Current directory: $(pwd)"

# Logical operators
ls && echo "Success" || echo "Failed"
false || echo "This will print"
\`\`\`

### Error Handling Tests
\`\`\`bash
# Invalid commands
nonexistent_command
ls /nonexistent/directory

# Permission errors
cat /etc/shadow

# Syntax errors
ls |
echo "unclosed quote
\`\`\`

### Signal Tests
- Press `Ctrl+C` during command execution
- Press `Ctrl+D` to exit
- Press `Ctrl+\` (should be ignored)

## ⚠️ Known Limitations

- **Subshells**: Limited support for complex subshell operations
- **Job control**: No background process management (`&`)
- **Aliases**: Command aliases not implemented
- **History**: Basic history, no persistent storage
- **Tab completion**: Not implemented
- **Globbing**: Limited wildcard support

## 🔍 Debugging

### Common Issues
1. **Memory leaks**: Use `valgrind` to check for memory issues
2. **Signal handling**: Ensure proper signal restoration
3. **File descriptor leaks**: Close all opened file descriptors
4. **Zombie processes**: Proper process cleanup with `wait()`

# Run with valgrind
valgrind --leak-check=full ./minishell
\`\`\`

## 📚 Resources

- [Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- [The Linux Programming Interface](https://man7.org/tlpi/)

## 👥 Authors

**[Benchahyd Mhammed]** - [GitHub Profile](https://github.com/yourusername)
**[Anbadi Anass]** - [GitHub Profile](https://github.com/partnername)

---

*This project is part of the 42 School curriculum and demonstrates system programming concepts including process management, signal handling, and shell implementation.*

---

*"The shell is the user's interface to the operating system."*

