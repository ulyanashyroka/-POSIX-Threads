# How the six programs work

Each program has its own `main()` and is compiled independently. POSIX threads share the same process address space, but each has its own execution state. `pthread_create()` starts a worker, and `pthread_join()` waits for a specific worker to finish. **Joining is not the same as protecting a shared variable during execution.**

## Problem 1 — One thread

**Requirement:** Create one thread that displays a message; main waits for it.

**Source:** [`src/problem1.c`](../src/problem1.c)

1. `pthread_t thread` declares a thread handle.
2. `pthread_create(&thread, NULL, worker, NULL)` starts `worker`. The second argument uses default attributes; the fourth passes no worker argument.
3. `worker` prints a message and returns `NULL`.
4. `pthread_join(thread, NULL)` blocks the main thread until the worker exits. Main then prints its completion message.

**Why:** Without joining, main could exit before the worker finishes. The worker message should precede the final main-thread message.

## Problem 2 — Five threads and IDs

**Requirement:** Five threads each print their assigned number and thread ID.

**Source:** [`src/problem2.c`](../src/problem2.c)

1. `pthread_t threads[5]` stores five thread handles.
2. `numbers[5] = {1,2,3,4,5}` supplies a **distinct stable address** for each worker. Passing `&i` (the loop variable) instead would risk workers observing changing values.
3. The first loop creates all five workers; each converts `void *arg` back to `int *`, dereferences it, and prints its number and `pthread_self()` identifier.
4. The second loop joins all five threads before main exits.

**Why:** The OS scheduler chooses when workers run; the output can be 1,4,2,5,3 or another order. The sample cast `(unsigned long)pthread_self()` is suitable for the target Mac but is not a universally portable way to format opaque `pthread_t` values. The `$` shown at the right edge of a Pico/nano screenshot can indicate a line continues offscreen; it is not necessarily a literal source-code character.

## Problem 3 — Returning a sum

**Requirement:** Worker sums integers 1 through 100 and returns the result to main.

**Source:** [`src/problem3.c`](../src/problem3.c)

1. `malloc(sizeof *result)` allocates an integer on the heap; returning the address of a worker's local stack variable would be invalid after it exits.
2. The worker initializes `*result = 0`, loops from 1 through 100, and returns the allocated pointer.
3. `pthread_join(thread, &returned)` waits and stores the worker's returned pointer.
4. Main checks for a null pointer, prints `*sum`, and calls `free(sum)` to avoid a memory leak.

**Why:** The result must remain valid after the worker terminates. Expected arithmetic sum: `100 * 101 / 2 = 5050`.

## Problem 4 — Three concurrent counters

**Requirement:** Three threads each print 1 through 10.

**Source:** [`src/problem4.c`](../src/problem4.c)

1. Three stable integer arguments identify the workers.
2. Each worker loops from 1 to 10, printing its own thread number and count.
3. Main joins all three workers, ensuring all 30 lines have been printed before exit.

**Why:** Lines from different workers *may* interleave, but visible interleaving is not guaranteed. One worker might print all ten lines before another gets CPU time. Per-worker counts should still progress 1 to 10.

## Problem 5 — Mutex-protected shared counter

**Requirement:** Five threads each increment one shared counter 1,000 times using a mutex.

**Source:** [`src/problem5.c`](../src/problem5.c)

1. Global `counter` is shared by all workers; `PTHREAD_MUTEX_INITIALIZER` creates the mutex.
2. Each worker repeats 1,000 times: lock mutex, increment counter, unlock mutex.
3. The lock covers the read-modify-write critical section, preventing two workers from updating the counter simultaneously.
4. Main joins every worker, prints the result, and destroys the mutex.

**Why:** `++counter` is not a safe unsynchronized shared update. Mutual exclusion prevents lost updates. With successful thread creation and synchronization, the final count is `5 * 1000 = 5000`.

## Problem 6 — No synchronization (intentional data race)

**Requirement:** Five threads increment a shared counter without a mutex and compare expected and actual results.

**Source:** [`src/problem6.c`](../src/problem6.c)

1. The same five workers each execute 1,000 `++counter` operations.
2. **There is deliberately no mutex or atomic operation** protecting the shared counter.
3. Main still joins the workers, then prints the arithmetic expectation (5000) and the actual counter observed in that run.
4. `pthread_join` waits for completion, but cannot repair conflicting updates that occurred earlier.

**Why:** Two threads can conceptually both read 100, both compute 101, and both write 101: one increment is lost. More precisely, the concurrent non-atomic accesses create a **C data race and undefined behavior**. A final result below 5000 is one possible symptom, but neither that value nor any specific value is guaranteed. Even a result of 5000 does not establish correctness. `-O0` makes an instructional run easier to inspect but does not remove undefined behavior.

## Synchronization comparison

| | Problem 5 | Problem 6 |
|---|---|---|
| Threads | 5 | 5 |
| Increments per thread | 1000 | 1000 |
| Shared variable | yes | yes |
| `pthread_join` | yes | yes |
| Mutex around increment | yes | no |
| Expected mathematical total | 5000 | 5000 |
| Guaranteed result (assuming successful execution) | 5000 | no |

## Submission checklist

- Submit all six `.c` source files.
- Include screenshots captured from your own Terminal executions.
- Explain `pthread_join` versus mutex synchronization.
- In Problem 6, state the **actual** results you observed; do not claim a lost update occurred unless the output shows it.
