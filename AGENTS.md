# Repository Guidelines

## Project Structure & Module Organization
This repository is organized as a study workspace for C programming.
- `repo recursos c/C-Seminars/`: main source set, split by topic folders (`001` to `015`) with one focused `.c` example per concept.
- `datasheet/`: reference documentation (for example `lpc17xx_um_unlocked.pdf`).
- `tps/`, `hecho en clase/`, `codex-made/`: reserved for coursework and generated material; currently mostly empty.
- `.vscode/`: local editor/debug settings.

When adding new examples, follow the existing numbered-topic pattern (for example `016/my_topic.c`).

## Build, Test, and Development Commands
There is no global build system yet (no `Makefile`/`CMakeLists.txt`). Build files directly with GCC.
- `gcc "repo recursos c/C-Seminars/001/hello_world.c" -o hello_world`
  Compiles one sample program.
- `./hello_world` (PowerShell: `./hello_world.exe`)
  Runs the compiled binary.
- `gcc -Wall -Wextra -pedantic "repo recursos c/C-Seminars/003/n_queens.c" -o n_queens`
  Compiles with stricter warnings for review-quality checks.

## Coding Style & Naming Conventions
- Language: C.
- Indentation: 4 spaces, braces on their own line (K&R/Allman hybrid as used in current files).
- File names: lowercase with underscores (example: `function_pointers.c`).
- Function names: descriptive; prefer `lowerCamelCase` when matching existing code (example: `solveNQueens`).
- Keep comments concise and instructional; avoid restating obvious lines.

## Testing Guidelines
No automated test framework is configured yet. Use compile-and-run validation per example.
- Treat `-Wall -Wextra -pedantic` as a minimum quality gate.
- Name future tests by target file, e.g., `tests/test_n_queens.c`.
- For interactive programs, document sample inputs/outputs in PR descriptions.

## Commit & Pull Request Guidelines
Git history is currently minimal (`first commit`), so conventions are lightweight.
- Use short, imperative commit messages: `add pointer arithmetic example`.
- Keep commits scoped to one topic or folder.
- PRs should include: what changed, why, commands used to compile/run, and console output snippets when behavior changes.
- Link related coursework/task IDs when applicable.
