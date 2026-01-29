# Challenge 1  ARM Calling Convention & Naked Functions (Cortex-M4)

## 1. Goal of this Lab

The goal of this lab is to **understand how function calls work at low level** on an **ARM Cortex-M4** and how **C code and assembly interact**.

In this challenge, we:

* Manually call a C function from assembly
* Respect the ARM calling convention (AAPCS)
* Use a **naked function** to control everything ourselves
* Store the function result in memory

---

## 2. What was implemented

We implemented a **wrapper function** using:

```c
__attribute__((naked))
```

This wrapper:

1. Loads two global variables (`x` and `y`)
2. Calls a normal C function `add_function(x, y)`
3. Retrieves the return value
4. Stores it in `add_result`
5. Returns correctly without compiler help

---

## 3. ARM Calling Convention (AAPCS)in simple words

AAPCS defines **rules** so functions can safely call each other.

### On ARM Cortex-M:

* **r0** → first argument
* **r1** → second argument
* **r2, r3** → next arguments (if any)
* **r0** → return value
* **lr** → return address

Example:

```c
add_function(x, y);
```

Means:

* `x` must be in `r0`
* `y` must be in `r1`
* result comes back in `r0`

---

## 4. What is a Naked Function

A **naked function** is a function where:

*  No `push`
*  No `pop`
*  No stack setup
*  No automatic return

The compiler generates **nothing** except the code we write.

### Why this matters

This allows us to:

* Control registers manually
* Understand how function calls really work
* Avoid hidden compiler behavior

⚠️ Because of this, **we must return manually** using:

```asm
bx lr
```

---

## 5.  what we learned :Registers and Stack 

### Stack Pointer (SP)

* Points to the top of the stack
* Stack grows downward
* Used for local variables and saved registers

### Frame Pointer (r7)

* Marks the start of a function stack frame
* Used by the compiler for debugging and variable access

### Stack Frame

* Memory used by one function call
* Contains:

  * Saved registers
  * Local variables
  * Return address

 In a naked function, **there is no stack frame unless we create one ourselves**.

---

## 6. Caller-saved vs Callee-saved registers

### Caller-saved (can be overwritten)

```
r0 r1 r2 r3 r12 lr
```

### Callee-saved (must be preserved)

```
r4 r5 r6 r7 r8 r9 r10 r11
```

### Important rule learned

> In a naked function, **we only save registers if we use callee-saved ones**.

Our wrapper uses only:

* `r0`, `r1`, `lr`

So:

* ✅ No `push`
* ✅ No `pop`
* ✅ Safe

---

## 7. How the wrapper works (step by step)

### 1️⃣ Load `x`

```asm
ldr r0, =x
ldr r0, [r0]
```

### 2️⃣ Load `y`

```asm
ldr r1, =y
ldr r1, [r1]
```

### 3️⃣ Call the C function

```asm
bl add_function
```

* `x` in `r0`
* `y` in `r1`
* result returned in `r0`

### 4️⃣ Store the result

```asm
ldr r1, =add_result
str r0, [r1]
```

### 5️⃣ Return manually

```asm
bx lr
```

---

## 8. Why `add_function` uses the stack

The C function `add_function` is compiled with `-O0`, so the compiler:

* Creates a stack frame
* Saves registers
* Stores parameters on the stack

This is **normal and correct**.

The wrapper does **not** use the stack.

---

## 9. Final result

After execution:

```c
x = 6
y = 9
add_result = 15
```

The wrapper successfully:

* Followed the ARM calling convention
* Called a C function from assembly
* Returned correctly from a naked function

---

## 10. What this lab teaches

✔ ARM calling conventions (AAPCS)
✔ How C and assembly interact
✔ How stack and registers work
✔ Why naked functions are dangerous but powerful
✔ How function calls really work on Cortex-M

---
