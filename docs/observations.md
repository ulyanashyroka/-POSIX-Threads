# Execution observations (fill in after running locally)

This is a template, **not** a record of measured results. Add your own screenshots under `screenshots/` and update the entries below.

| Problem | Expected / check | Actual output | Screenshot |
|---|---|---|---|
| 1 | Worker message before main completion | TODO | TODO |
| 2 | Five unique assigned numbers and IDs; order may vary | TODO | TODO |
| 3 | Sum = 5050 | TODO | TODO |
| 4 | 30 lines; each thread counts 1–10 | TODO | TODO |
| 5 | Final counter = 5000 | TODO | TODO |
| 6 | Expected = 5000; actual not guaranteed | TODO | TODO |

## Problem 6 repeat runs

Run `./problem6` at least five times and record each **actual** counter value:

| Run | Expected | Actual |
|---|---:|---:|
| 1 | 5000 | TODO |
| 2 | 5000 | TODO |
| 3 | 5000 | TODO |
| 4 | 5000 | TODO |
| 5 | 5000 | TODO |

**Interpretation:** If an actual count differs from 5000, describe the discrepancy as a possible manifestation of unsynchronized updates. If all runs show 5000, state that no discrepancy was observed in these runs, **not** that the code is race-free. In C, this shared non-atomic counter has a data race regardless of the printed number.
