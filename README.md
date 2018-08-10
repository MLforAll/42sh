# 42sh
42 school's 42sh (main shell) project

Continuation of the previous shell projects -- 21sh and minishell

# Main goals:

- Proper job control
- Globbing
- POSIX Buitlins
- Read builtins

# Features:

- Lexer, Parser, AST
- Pipes
- fd redirections and closing
- Local variables
- Set variables with text (only)
- Customisable prompt with `SH_PROMPT` variable
- Autocompletion (zsh style)
- Globbing
- POSIX builtins
- Read builtin
- Job Control

# Line-editing Features:

- Move your cursor arround with left and right keys
- Jump home/end of the line
- Multiline editing
- Copy/Cut/Paste
- Move between lines
- Automatic color removal for prompt
- Dumb mode with one-line editing

# Example usages:

`$> 42sh /path/to/script` or `$> cat /path/to/script | 42sh` runs the script with 42sh. It exists after the script ran.

`$> 42sh` runs an interactive shell.

# Changelog:

_Tuesday 10th August 2018:_
Repo created with copy of 21sh's repo
