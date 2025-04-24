# 🧮 ALU Opcodes Übersicht

## ➕ Arithmetic
| Opcode | Beschreibung                        |
|--------|-------------------------------------|
| `ADD`  | Addition                            |
| `SUB`  | Subtraktion                         |
| `NEG`  | Negation von `inA` (`0 - inA`)      |
| `INC`  | Inkrementiere `inA` um `+1`         |
| `DEC`  | Dekrementiere `inA` um `-1`         |

---

## ✖️ Multiplication
| Opcode | Beschreibung               |
|--------|----------------------------|
| `MUL`  | Multiplikation (Unsigned)  |
| `IMUL` | Multiplikation (Signed)    |

---

## ➗ Division
| Opcode | Beschreibung               |
|--------|----------------------------|
| `DIV`  | Division (Unsigned)        |
| `IDIV` | Division (Signed)          |

---

## ⚙️ Bitwise Logic
| Opcode | Beschreibung               |
|--------|----------------------------|
| `AND`  | Bitweises UND              |
| `OR`   | Bitweises ODER             |
| `XOR`  | Exklusives ODER            |
| `NOT`  | Bitweise Invertierung      |
| `NAND` | Negiertes UND              |
| `NOR`  | Negiertes ODER             |

---

## 🔀 Shifts & Rotates
| Opcode | Beschreibung                                     |
|--------|--------------------------------------------------|
| `SHL`  | Logischer Shift nach links                       |
| `SHR`  | Logischer Shift nach rechts                      |
| `SAL`  | Arithmetischer Shift nach links (Vorzeichen bleibt) |
| `SAR`  | Arithmetischer Shift nach rechts (Vorzeichen bleibt) |
| `ROL`  | Rotate Left: Shift mit Bit-Einfügen von rechts   |
| `ROR`  | Rotate Right: Shift mit Bit-Einfügen von links   |

---

## 🌊 Floating Point Operations
| Opcode | Beschreibung                          |
|--------|---------------------------------------|
| `FADD` | Float Addition                        |
| `FSUB` | Float Subtraktion                     |
| `FMUL` | Float Multiplikation                  |
| `FDIV` | Float Division                        |
| `FNEG` | Float Negation                        |
| `FSQRT`| Quadratwurzel                         |
| `FABS` | Absolutbetrag                         |
| `FTOI` | Float → Integer                       |
| `ITOF` | Integer → Float                       |
| `FCMP` | Float-Vergleich (mit Flags)           |
| `FMIN` | Minimum zweier Floats                 |
| `FMAX` | Maximum zweier Floats                 |

---

# 🏳️ ALU Flags

| Flag   | Bedeutung           |
|--------|---------------------|
| `Z`    | Zero (Ergebnis ist 0)     |
| `N`    | Negative (Vorzeichen-Bit gesetzt) |
| `C`    | Carry (Unsigned Overflow) |
| `V`    | Overflow (Signed Overflow) |
| `NAN`  | Not a Number (bei Floats) |
| `INF`  | Infinity (±∞ bei Floats)  |
| `U`    | Underflow (z. B. bei `0 - x`) |

---