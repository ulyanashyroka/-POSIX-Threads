# POSIX Threads in C: Six Exercises

A practical introduction to creating threads, joining them, returning values, concurrent scheduling, mutexes, and data races.

## Quick start (macOS)

This project uses POSIX threads (`pthread.h`). On this Mac, the default `clang` resolves to MacPorts LLVM 18 and previously failed to locate `stdio.h`. Use Apple's compiler through `xcrun clang`:

```sh
xcrun clang -Wall -Wextra -pthread src/problem1.c -o problem1
./problem1
```

For all exercises:

```sh
for n in 1 2 3 4 5 6; do
  xcrun clang -Wall -Wextra -pthread -O0 "src/problem${n}.c" -o "problem${n}" || exit 1
done
```

Run one at a time with `./problem2`, etc. See [setup and troubleshooting](docs/setup.md) and [step-by-step explanations](docs/exercises.md).

## Assignment map

| Exercise | Task | Key idea |
|---|---|---|
| 1 | One worker prints a message | `pthread_create`, `pthread_join` |
| 2 | Five workers print number and ID | thread arguments, nondeterministic order |
| 3 | Worker sums 1–100 | returning heap-allocated result through `pthread_join` |
| 4 | Three workers each count 1–10 | interleaving and scheduling |
| 5 | Five workers increment shared counter 1,000 times each | mutex-protected critical section |
| 6 | Same increments without a mutex | data race, possible lost updates |

## Results and evidence

The expected sum in Exercise 3 is **5050**. Exercise 4 should print 30 counting lines, although their order is not fixed. Exercise 5 should print **5000**. Exercise 6 has an expected arithmetic total of **5000**, but its actual result is not guaranteed: the C program has a data race and therefore undefined behavior. Seeing 5000 does **not** prove that it is safe.

Capture **your own** terminal screenshots for all six exercises and add them to `screenshots/` before submitting. No screenshots or measured results are invented in this repository. See [observations template](docs/observations.md).

## Repository layout

- `src/`: separate compilable C source for each problem.
- `docs/setup.md`: installation, build and troubleshooting.
- `docs/exercises.md`: annotated explanation of every program, how and why.
- `docs/observations.md`: instructions and placeholders for actual output observations.

## Assignment source

Based on the supplied *POSIX Threads Assignment: Problems 1–6* and *POSIX Threads Problems 1–5 Solutions*. Problem 6 is implemented as the requested unsynchronized comparison; it was not included in the supplied reference solutions.
