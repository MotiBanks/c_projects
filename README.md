# Bit Manipulation Notes

**Author:** Moti  

This repo holds my walk-through and thought process while solving some Data Lab puzzles.  
These are my notes — my understanding of what each puzzle is trying to teach me, how I reason about the solution, and why the operations work.

I’m keeping it simple, honest, and in my tone… just organized so my future self (or anyone reading) can follow what I was thinking.  

---

## 🧩 Puzzle 1 — `bitAnd`

**Goal:** compute `x & y` using only `~` (NOT) and `|` (OR).  
**Allowed ops:** `~` `|`

### 🔍 Explanation

The puzzle says: implement bitAND `(x & y)` without actually using `&`.  

So we rely on De Morgan’s Law, which I understand as:



`not(A and B) = not(A) or not(B)`

`not(A or B) = not(A) and not(B)`


If the question had been:

`~(x & y)`

Then by De Morgan:

`~(x & y) = ~x | ~y`


But the puzzle is the inverse problem: 
compute `(x & y)`.

Using the same law:

`(x & y) = ~(~x | ~y)`



### ✅ Final solution
```c
return ~(~x | ~y);
```


---


## Puzzle 2 — `getByte`

**Goal:** extract the n-th byte from `x`.  
**Allowed ops:** shifts + mask.

### 🔍 Step-by-step logic

1 byte = 8 bits
nth byte → `n * 8`

But we cannot use `*` in this puzzle since it is not part of the allowed ops.

Since 8 is a power of 2 (8 = 2³), we can rewrite:

`n * 8 → n << 3`


So far:

`(n << 3)`


Next, to get the nth byte from `x` we need to **shift x right** by that amount.

The idea being:

`“To extract a piece of a number, you move it to the front before masking.”`

Right shifting moves the desired byte to the lowest 8 bits:

`x >> (n << 3)`


Once it’s moved, we mask with `0xFF`:

Masking = selecting only the bits we want and ignoring everything else.

So:

`(x >> (n << 3)) & 0xFF`



### ✅ Final solution
```c
return (x >> (n << 3)) & 0xFF;
```