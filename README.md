# 🐚 Minishell – My Custom Unix Shell Implementation

This project consists of building a simple Unix shell from scratch, mimicking key functionalities of Bash. It's a deep dive into how shells really work, and gave me hands-on experience with process management, file descriptors, command parsing, and much more.

## 🚀 What I Built

Minishell is a fully functional, interactive shell program that supports:

- Prompt display and user input handling
- Execution of **built-in commands**:
  - `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Parsing and execution of **external commands**, searching via `$PATH`
- Handling of **quotes**, **pipes (`|`)**, and **redirections** (`>`, `<`, `>>`)
- Management of **environment variables**, including `$?` (exit code)
- **Signal handling** (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) for user interrupts
- **Command history navigation** using up/down arrows (termcap-based)

The shell was implemented in C using only allowed standard library functions, ensuring full manual control of processes, memory, and I/O.


## 🧠 Key Skills Demonstrated

✔️ Advanced understanding of **UNIX process control**: `fork()`, `execve()`, `pipe()`, `dup2()`  
✔️ Implementation of **custom parsers and tokenizers** for CLI commands  
✔️ Management of **file descriptors and redirection logic**  
✔️ Robust **memory management** (no leaks, manual `malloc`/`free`)  
✔️ Construction of a full **Makefile** with clean build rules  
✔️ Use of **termcap** to enhance user interaction (command history, cursor movement)  
✔️ Mastery of **defensive programming** (segfault-proof, norm-compliant)


## 📁 Project Structure
├── src/ # Source files for parsing, execution, built-ins, etc.
├── includes/ # Header files
├── libft/ # Custom C standard library
├── Makefile # Build system




## 🧪 How to Run

```bash
git clone https://github.com/rgu-rebeca/minishell
cd minishell
make
./minishell

Try commands like:

echo Hello world
ls -l | grep .c > out.txt
export VAR=value 

