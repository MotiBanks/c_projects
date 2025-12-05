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
