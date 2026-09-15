# SampleProject

## Purpose
A simple C++ command-line calculator built to practice a complete Git workflow —
branching, merging, conflict resolution, stashing, and GitHub collaboration.

## Files
- `main.cpp` — Calculator class (add, subtract, multiply, power, divide, remainder)
- `notes.txt` — scratch notes / planning
- `.gitignore` — ignores compiled binaries and editor files
- `README.md` — this file

## Git Workflow Followed
- Created 3 feature branches, each adding one calculator operation
- Merged them into `main`, including resolving a real merge conflict where two
  branches both edited the same lines of `main.cpp`
- Used `git stash` to shelve in-progress work while switching branches
- Pushed to GitHub, and verified by cloning into a second folder and pulling
