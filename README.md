# SampleProject

## Purpose
A simple C++ command-line calculator built to practice a complete Git workflow —
branching, merging, conflict resolution, stashing, GitHub collaboration, and advanced
history management.

## Features
The `Calculator` class supports:
- Addition
- Subtraction
- Multiplication
- Power (exponentiation)
- Division (with a zero-check to avoid divide-by-zero errors)
- Remainder (using int cast, since `%` needs integer operands)
- Square Root
- Percentage

## Files
- `main.cpp` — Calculator class and program entry point
- `notes.txt` — scratch notes and planning used during development
- `.gitignore` — ignores compiled binaries and editor/OS files
- `README.md` — this file
- `phase2_report.md` — report of advanced Git operations performed

## Git Workflow Followed
- Created feature branches (`feature/power`, `feature/division`, `feature/remainder`),
  each adding one calculator operation
- Merged them into `main`, including resolving a real merge conflict where two branches
  edited the same lines of `main.cpp`
- Used `git stash` to shelve in-progress work while switching branches to do other work
- Pushed the project to GitHub, then verified by cloning into a second folder and pulling
- Opened one GitHub Issue and completed one Pull Request (`feature/sqrt` merged into `main`)
- Practiced undo and history commands: `git log`, `git reflog`, `git reset`, `git revert`,
  `git commit --amend`
- Practiced advanced Git commands: interactive rebase (squash), `git blame`, `git clean`,
  `git cherry-pick`, and created release tag `v1.0`

## How to Run
```bash
g++ -o calc main.cpp
./calc
```
Enter two numbers when prompted to see the results of all supported operations.
