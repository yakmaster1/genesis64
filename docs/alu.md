#Opcodes

**Arithmetic**:
- ADD
- SUB
- NEG (Negation of input A)
- INC (Increment input A)
- DEC (Decimate input A)

**Multiplication**:
- MUL (Unsigned)
- IMUL (Signed)

**Division**:
- DIV (Unsigned)
- IDIV (Signed)

**Logic**: (Bitwise)
- AND
- OR
- XOR
- NOT
- NAND
- NOR

**Shifts**:
- SHL (Shift to left)
- SHR (Shift to right)
- SAL (Arithmetic shift to left -> Signed bit stays)
- SAR (Arithmetic shift to right -> Signed bit stays)
- ROL (Rotate left -> Shift with insert of bit)
- ROR (Rotate right -> Shift with insert of bit)

**Float OPs**:
- FADD
- FSUB
- FMUL
- FDIV
- FNEG
- FSQRT (Square root)
- FABS (Absolute value)
- FTOI (Float to Integer)
- ITOF (Integer to float)
- FCMP (Float compare)
- FMIN (The minimum value of 2 floats)
- FMAX (The maximum value of 2 floats)

# Flags

Z -> Zero
N -> Negative
C -> Carry
V -> Overflow
NAN -> Not a number
INF -> Infinity
U -> Underflow
