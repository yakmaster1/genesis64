# 🧮 ALU Opcodes Übersicht

## ➕ Arithmetic
| Opcode | Beschreibung                        |
|--------|-------------------------------------|
| `ADD`  | Addition                            |
| `SUB`  | Subtraktion `[^1]`                     |
| `NEG`  | Negation von `inA` [2]              |
| `INC`  | Inkrementiere `inA` um `+1`         |
| `DEC`  | Dekrementiere `inA` um `-1`         |

---

## ✖️ Multiplication
| Opcode | Beschreibung               |
|--------|----------------------------|
| `MUL`  | Multiplikation             |
| `IMUL` | Signed Multiplikation      |

---

## ➗ Division
| Opcode | Beschreibung               |
|--------|----------------------------|
| `DIV`  | Division                   |
| `IDIV` | Signed Division            |

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
| Opcode | Beschreibung                                          |
|--------|--------------------------------------------------     |
| `SHL`  | Logischer Shift nach links                            |
| `SHR`  | Logischer Shift nach rechts                           |
| `SAL`  | Arithmetischer Shift nach links (Vorzeichen bleibt)   |
| `SAR`  | Arithmetischer Shift nach rechts (Vorzeichen bleibt)  |
| `ROL`  | Rotate Left: Shift mit Bit-Einfügen von rechts        |
| `ROR`  | Rotate Right: Shift mit Bit-Einfügen von links        |

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

| Flag   | Bedeutung                             |
|--------|---------------------                  |
| `Z`    | Zero (Ergebnis ist 0)                 |
| `N`    | Negative (Vorzeichen-Bit gesetzt)     |
| `C`    | Carry (Unsigned Overflow)             |
| `V`    | Overflow (Signed Overflow) [3]        |
| `NAN`  | Not a Number (bei Floats)             |
| `INF`  | Infinity (±∞ bei Floats)              |
| `U`    | Underflow (z. B. bei `0 - x`) [4]     |

---


- [1]: Subtraktion ist eine der vier Grundoperationen der Arithmetik und wird in digitalen Systemen durch Zweierkomplement-Addition realisiert. Anstatt zwei Zahlen direkt zu subtrahieren, berechnet der Prozessor:
```A - B ≡ A + (B + 1)```
Dabei wird B bitweise invertiert (~B) und anschließend 1 addiert, was der Bildung des Zweierkomplements entspricht. Diese Methode erlaubt es, Subtraktion mit derselben Schaltung wie Addition durchzuführen, was die Hardware vereinfacht. Bei der Subtraktion mit unsigned Zahlen tritt ein Underflow auf, wenn der Minuend (A) kleiner als der Subtrahend (B) ist. Bei signed Zahlen erkennt die ALU einen Overflow (V), wenn das Ergebnis außerhalb des darstellbaren Bereichs für Zweierkomplement-Zahlen liegt.

- [2]: Signed Zahlen sind ganze Zahlen, die sowohl positive als auch negative Werte darstellen können. In der Computertechnik werden sie üblicherweise im Zweierkomplement gespeichert, wobei das höchstwertige Bit (MSB) als Vorzeichenbit dient: 0 steht für positive, 1 für negative Werte.

- [3]: Overflow tritt auf, wenn das Ergebnis einer arithmetischen Operation den darstellbaren Zahlenbereich eines Datentyps überschreitet. Bei signed Werten passiert das, wenn zwei positive Zahlen ein negatives Ergebnis erzeugen oder zwei negative Zahlen ein positives.

- [4]: Underflow tritt auf, wenn das Ergebnis einer Subtraktion im unsigned Kontext negativ wäre, was in binären Systemen nicht darstellbar ist bzw. dass das Ergebnis negativ wäre, aber durch die fehlende Vorzeichenunterstützung des Typs zurück auf einen hohen Wert „überläuft“. Im signed Kontext gibt es keinen klassischen Underflow, da negative Ergebnisse gültig sind. Der einzige relevante Fehlerzustand ist der signed Overflow, der auftritt, wenn das Ergebnis kleiner als `INT_MIN` (4 Bit = 1000) oder größer als `INT_MAX` (4 Bit = 0111) ist.