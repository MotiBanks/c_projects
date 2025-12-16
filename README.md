# **Bit Manipulation Notes**

**Author:** Moti  

This repo holds my walk-through and thought process while solving some Data Lab puzzles.  
These are my notes — my understanding of what each puzzle is trying to teach me, how I reason about the solution, and why the operations work.

I’m keeping it simple, honest, and in my tone… just organized so my future self (or anyone reading) can follow what I was thinking.  

---

# **Puzzle 1 — `bitAnd`**

**Goal:** compute `x & y` using only `~` (NOT) and `|` (OR).  
**Allowed ops:** `~` `|`

## **🔍 Explanation**

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



## **✅ Final solution**
```c
return ~(~x | ~y);
```


---


# **Puzzle 2 — `getByte`**

**Goal:** extract the n-th byte from `x`.  
**Allowed ops:** shifts + mask.

## **🔍 Step-by-step logic**

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



## **✅ Final solution**
```c
return (x >> (n << 3)) & 0xFF;
```


---


# **Puzzle 3 - `logicalShift`**

**Goal:** Perform a logical right shift (fill with zeros), even if machine uses arithmetic shift.  
**Allowed ops:** shifts + mask.


## **Reasoning**
Perform a Logical Right Shift on a Signed Integer??

It's impossible just reading it.

In C, the **rule for shifting is:**

`Unsigned integers → logical right shift (fills with zeros)`

`Signed integers → arithmetic right shift (preserves the sign bit)`

But here, the puzzle asks us to do a logical right shift on a signed integer.


## **🔍 Step-by-step logic**

## **Step 1:** Start with an arithmetic right shift

We could just do:

`x >> n`


But this is not what the puzzle wants....


Arithmetic right shift will always preserves the sign bit, which for negative numbers is 1.

Logical right shift fills with zeros.   

We don’t want the extra sign bits. 



## **Step 2:** Introduce masking

We need masking to remove the extra 1’s that the arithmetic right shift produces.

**Quick note: we’re assuming a 32-bit system here, so the total number of bits is 32.**
**That’s why later you’ll see 32 - n.**

Now the question is what part of this bits do we want to keep??

- After shifting right by n, we want to keep the **lower 32 - n bits** .

- The top n bits are garbage; the lower bits are our real data.

So the first idea is to create an indicator for where the lower bits start:

`1 << (32 - n)`


Why 1 ?

**Because you cannot create new 1s from 0 while using a shift — shifts only moves existing bits.**

So using 1, will give us a number with one 1 and a bunch of zeros , marking the start of the bits we want.



 ## **Step 3:** Expand the mask

If we stopped here, `1 << (32 - n)` would keep only one bit and erase all our data.
We subtract 1:

`(1 << (32 - n)) - 1`


Why?

**Subtracting 1 in binary turns the lone 1 into 0 and all zeros to its right into 1s.`**

This gives us:
- *n zeros* on the left 
-  `32 - n` ones on the right, exactly the mask we need.


## **✅ Final result:**
```c
return (1 << (32 - n)) - 1;
```

we apply this mask after the arithmetic shift to simulate a logical right shift on a signed integer.


---



# **Puzzle 4 - `bitCount`**

**Goal:** Count how many 1 bits are inside x.  
**Allowed ops:** Only bit stuff. No loops.


## **How I should think about it**

I pretend the 32 bits in x are **32 little boxes**.  
Each box is either:

- 1 → has a stone
    
- 0 → empty
    

I’m not allowed to count them one by one.  
So I do a trick:

**I combine boxes into bigger boxes and add their stone counts.**

Each round doubles the size of the box groups.




## **Step 0: Make masks**

Masks are just **stencils** that let some boxes through and block the others.

- `0x55555555` → 010101010101…0101
    
    - Lets **every even bit** pass
        
    - Blocks **odd bits**
        
- `0x33333333` → 001100110011…0011
    
    - Lets every **2-bit group** pass
        
- `0x0f0f0f0f` → 0000111100001111…00001111
    
    - Lets every **4-bit group** pass
        

Think of masks as **cookie cutters**. They let you separate pieces to add properly.



## **Step 1: Count every 2 bits (pair of boxes)**

`x = (x & 0x55555555) + ((x >> 1) & 0x55555555);`

**Break it down:**

1. `(x & 0x55555555)` → keeps **even-numbered bits**
    
    - Bit 0, 2, 4, 6…
        
    - All other bits become 0
        
2. `(x >> 1)` → shifts all bits **1 to the right**
    
    - Now **odd-numbered bits** move into even spots
        
    - Then `& 0x55555555` → keeps them, blocks the rest
        
3. `+` → add the even bits and the odd bits **pair by pair**
    

**Result:**  
Each **2-bit pair** now contains the **count of 1s in those 2 bits** (0,1,2).



## **Step 2: Count every 4 bits (group of 2 pairs)**

`x = (x & 0x33333333) + ((x >> 2) & 0x33333333);`

**Break it down:**

1. `(x & 0x33333333)` → keeps the first **2-bit count** of each 4-bit group
    
2. `(x >> 2)` → shifts the **second 2-bit count** into the first spot
    
3. `& 0x33333333` → clears extra bits
    
4. `+` → adds the two 2-bit counts together
    

**Result:**  
Now each **4-bit group** has a number = count of 1s in those 4 bits (0–4).



## **Step 3: Count every 8 bits (group of 4-bit counts)**

`x = (x + (x >> 4)) & 0x0f0f0f0f;`

**Break it down:**

- `(x + (x >> 4))` → adds **two 4-bit counts**
    
- `& 0x0f0f0f0f` → clears overflow to keep each byte correct
    

**Result:**  
Each **8-bit chunk** = count of 1s in those 8 original bits (0–8).



## **Step 4: Combine 8-bit chunks into 16-bit**

`x = x + (x >> 8);`

- Adds first 8 bits + second 8 bits → 16-bit count
    
- Repeat for the next 16 bits
    



## **Step 5: Combine 16-bit chunks into 32-bit total**

`x = x + (x >> 16);`

- Adds first 16 bits + last 16 bits → total count in bottom 32 bits
    



## **Step 6: Keep only needed bits**

`return x & 0x3f;`

- Max number of 1s in 32-bit number = 32
    
- 32 in binary = 100000 → fits in **6 bits**
    
- `& 0x3f` keeps only these 6 bits, ignores junk
    



## ✅ **Final result**
```c
return x & 0x3f; 
```



## **How to remember it**

1. Think of **32 boxes**, each 0 or 1
    
2. Group them **2 → 4 → 8 → 16 → 32**
    
3. Add counts inside each group
    
4. Keep only enough bits for the max total
    


---




# **Puzzle 5 - `bang`**


**Goal:** Compute !x without using !   
**Allowed ops:** Use properties of two's complement: x | -x


## **What the puzzle wants**  
Build a function `bang(x)` that returns:

- **1 when x = 0**
    
- **0 when x ≠ 0**
    

And you’re **not allowed to use `!`**.



## **🔍 Step-by-step logic**

In two’s-complement:

- For **any nonzero x**, either **x** or **−x** must have its **sign bit = 1**.
    
- For **x = 0**, both x and −x are just **0**, so the sign bit is **0**.
    

This gives a simple detector:

### **If x ≠ 0 → (x | -x) has sign bit = 1**

### **If x = 0 → (x | -x) = 0**

So `(x | -x)` is the **“is-nonzero” signal**.



## **What OR ( | ) does**

Bitwise OR sets each bit to:

- **1** if either input bit is 1
    
- **0** only if _both_ bits are 0
    

So OR’ing x with −x forces the sign bit on for any nonzero x.



## **Walkthrough Example (x = 5 in 8-bit just for clarity)**

x = 5 → `0000 0101`

Compute −x:

- Flip bits: `1111 1010`
    
- Add 1:  `1111 1011`
    

Now OR them:

`0000 0101  |  1111 1011 ----------- 1111 1111`

That’s all 1s → sign bit = 1.



## **Right Shift Step**

Right-shifting by 7 in 8-bit (or 31 in 32-bit) does sign extension:

- If sign bit = 1 → shift fills with 1s → result = −1
    
- If sign bit = 0 → shift fills with 0s → result = 0
    

In this case:

`1111 1111 >> 7 = 1111 1111` → still `-1`

So after shifting:

- **x ≠ 0 → result = −1**
    
- **x = 0 → result = 0**
    

But the puzzle wants:

- **x ≠ 0 → 0**
    
- **x = 0 → 1**
    

Simple fix: **add 1**.

- If result = −1 → −1 + 1 = 0
    
- If result = 0 → 0 + 1 = 1
    




## **✅ Final result**
```c
return `((x | -x) >> 31) + 1`;
```

- If x = 0 → gives **1**
    
- If x ≠ 0 → gives **0**
    


---



# **Puzzle 6 - `tmin`**

**Goal:** Return minimum two's complement integer (0x80000000 for 32-bit)   
**Allowed ops:** <<



## **What the puzzle is _actually_ asking me to do**

The puzzle says:

> Return minimum two’s complement integer (0x80000000 for 32-bit)


## **Where to start reasoning (this is the key)**

I **do not** start with math.  
I **do not** start with C syntax.

I start by asking one blunt question:

> “What do the bits look like in the answer?”

And the puzzle literally tells me:

`0x80000000`

Since, Hex is just shorthand for bits. That hex number means:


`1000 0000 0000 0000 0000 0000 0000 0000`

So my brain should lock onto this:

- Exactly **one** bit is `1`
    
- It’s the **leftmost** bit
    
- Everything else is `0`
  

## **How do I physically assemble it?**
  
  Next blunt question:

> “What’s the simplest thing I can start from?”

Answer:  
`1`

Because `1` is literally:

`00000000 00000000 00000000 00000001`



## **Enter the only operation that moves bits**
The goal is to move the bits to the leftmost side

We Left shift (`<<`) means:

> Slide bits left. Drop zeros in behind.

After 31 steps, the bit has nowhere else to go.

It lands here:

`10000000 00000000 00000000 00000000`

Which is **exactly** what the puzzle asked for.


## **Why this equals “minimum integer”**

In Two's complement , the most important rule is:

> The leftmost bit (b31) is the **sign bit**

- If b31 = 0 → number is **non-negative** (OFF)
    
- If b31 = 1 → number is **negative** (ON)


So when:

- That bit one is on
    
- And all others are off
    

We literally have:

- The minimum negative value
    
- With no positive bits to counter it

## **✅Final result**
```c
return  1 << 31;
```


---


# **Puzzle 7 - `fitsBits`**
**Goal:** Return 1 if x fits in n-bit signed integer, else 0   
**Allowed ops:** << , >>



## **What the function is _really_ asking?**

“If I were forced to store `x` in only `n` bits, would its meaning survive?”


## **What does “fits in n bits” mean mechanically?**

In two’s complement, an `n`-bit signed number has:

- 1 sign bit
    
- n−1 value bits


## **The key physical idea (this is the whole trick)**

The mechanical fact I must internalize:

> If a number fits in `n` bits, then **throwing away all higher bits and then sign-extending back** gives you the _same number_.

That’s the definition of “fits”.

So the real test becomes:

> “If I shrink `x` to `n` bits and then grow it back to 32 bits, do I get the same `x`?”

If yes → it fits  
If no → information was lost → it doesn’t fit


## **How then do I “shrink” bits?**

We use **right shifts**.

Arithmetic right shift (`>>`) does this:

- Shifts bits right
    
- Copies the sign bit on the left
    

If we want to keep only the lowest `n` bits, we can:

1. Shift left to **throw away** high bits
    
2. Shift right to **restore** size with sign extension



Mechanically:

`shift = 32 - n `

`(x << shift) >> shift`

What this does:

- `x << shift` pushes important bits to the top, discarding excess
    
- `>> shift` brings it back down, filling with sign bits
    

If `x` truly fits in `n` bits, this round trip changes nothing.


And In bitwise terms:

- Equality → result 1
    
- Inequality → result 0


#### Case 1: Does **not** fit

```c
x = 4, n = 3 

shift = 32 - 3 = 29

(4 << 29) >> 29 = -4  // ≠ 4, so does NOT fit 

fitsBits(4, 3) = 0

```

#### Case 2: Fits
```c
x = -4, n = 3 

shift = 32 - 3 = 29  

(-4 << 29) >> 29 = -4  // same as original, so fits 

fitsBits(-4, 3) = 1
```


## **What to train my brain to ask next time?**

When you see:

> “fits in N bits”

Your first thought should be:

> “What happens if I compress it and expand it again?”

## **✅Final result**
```c
return (x << (32 - n)) >> (32 - n) == x;
```
