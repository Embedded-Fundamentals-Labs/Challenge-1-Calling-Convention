# Challenge 1 – Calling Convention (C ↔ ASM)

## Goal
Fix the wrapper function so it correctly calls a C function using the  
ARM Cortex-M4 calling convention.

The wrapper must:
- Call `add_function(x, y)`
- Store the result into `add_result`
- Work correctly as a `__attribute__((naked))` function

---

## What to do
- Create your own branch
- Implement the solution
- Make sure `add_result` contains the expected value after execution

---
