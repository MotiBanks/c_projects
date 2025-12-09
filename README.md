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


---


## Puzzle 3 - `logicalShift`

**Goal:** Perform a logical right shift (fill with zeros), even if machine uses arithmetic shift.  
**Allowed ops:** shifts + mask.


### Reasoning
**Perform a Logical Right Shift on a Signed Integer??**

It's impossible just reading it.

In C, the rule for shifting is:

`Unsigned integers → logical right shift (fills with zeros)`

`Signed integers → arithmetic right shift (preserves the sign bit)`

But here, the puzzle asks us to do a logical right shift on a signed integer.


### 🔍 Step-by-step logic

> ### **Step 1:** Start with an arithmetic right shift

We could just do:

`x >> n`


…but this is not what the puzzle wants.


Arithmetic right shift will always preserves the sign bit, which for negative numbers is 1. 

Logical right shift fills with zeros.   

We don’t want the extra sign bits. 



>### **Step 2:** Introduce masking

We need masking to remove the extra 1’s that the arithmetic right shift produces.

`Quick note: we’re assuming a 32-bit system here, so the total number of bits is 32. That’s why later you’ll see 32 - n.`

Now the question is what part of this bits do we want to keep??

After shifting right by n, we want to keep the `lower 32 - n bits`.

`The top n bits are garbage; the lower bits are our real data.`

So the first idea is to create an indicator for where the lower bits start:

`1 << (32 - n)`


Why 1??

`Because you cannot create new 1s from 0 while using a shift — shifts only moves existing bits.`

So using 1, will give us a number with one 1 and a bunch of zeros , marking the start of the bits we want.



> ### **Step 3:** Expand the mask

If we stopped here, `1 << (32 - n)` would keep only one bit and erase all our data.
We subtract 1:

`(1 << (32 - n)) - 1`


Why?

`Subtracting 1 in binary turns the lone 1 into 0 and all zeros to its right into 1s.`

This gives us `n zeros` on the left and `32 - n` ones on the right, exactly the mask we need.


### ✅ Final result:
```c
return (1 << (32 - n)) - 1;
```

we apply this mask after the arithmetic shift to simulate a logical right shift on a signed integer