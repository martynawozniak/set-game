# SET Endgame Simulator

This project is an implementation of a SET card game endgame simulator written in C.
It reproduces the mechanics of the game with simplified rules tailored for algorithmic simulation. 

## Notes
This project was implemented as part of an academic assignment in the course **Introduction to Programming**.

## Project Structure
```bash
├── set_simulator.c   # Main program source code
├── example1.in       # Example input and output files are provided externally
├── example1.out
├── example2.in
├── example2.out
├── example3.in
├── example3.out
└── README.md
```

## Game Rules

- SET is a real-time card game played with **81 unique cards**.  
- Each card has **4 attributes**, each taking one of **3 values**:
  1. **Number of symbols**: 1, 2, or 3  
  2. **Color**: red, green, or purple  
  3. **Shading**: empty, striped, or solid  
  4. **Shape**: diamond, squiggle, or oval  

- A **SET** is a group of three cards where, for each attribute, the values are either:
  - all the same, or  
  - all different  

- The game starts with **12 cards on the table** (or fewer if the deck has less than 12).  
- When a SET is found, the three cards are removed and replaced (if possible).  
- If no SET exists, **3 more cards** are drawn from the deck.  
- The game ends when:
  - the deck is empty **and**  
  - no more SETs can be formed.

## Program Description

The program simulates the **end of a SET game**, assuming:
- Players always pick the **first available SET** in lexicographic order of positions.  
- If no SET is available, 3 more cards are added (until the deck is empty).  

### Input
- A sequence of integers between `1111` and `3333`, with no repetitions.  
- Each integer encodes a card:
ABCD →
A = number of symbols (1–3)
B = color (1–3)
C = shading (1–3)
D = shape (1–3)

- Input length is always divisible by 3.  
- Cards are formatted with arbitrary spaces/newlines.  

### Output
The program prints:
- Initial table state.  
- Sequence of moves until the game ends.  
- Table state after each move.  

Format:
- `= ...` → current table cards  
- `- ...` → cards forming a SET  
- `+` → no SET found, 3 cards added

## Compilation & Execution

The project is designed to compile under **C17 rules** with GCC:

```bash
gcc -std=c17 -pedantic -Wall -Wextra -Wformat-security \
    -Wduplicated-cond -Wfloat-equal -Wshadow -Wconversion \
    -Wjump-misses-init -Wlogical-not-parentheses \
    -Wnull-dereference -Wvla -Werror \
    -fstack-protector-strong -fsanitize=undefined \
    -fno-sanitize-recover -g -fno-omit-frame-pointer -O1 \
    set_simulator.c -o set_simulator
```
Run the program with:

```bash
./set_simulator < input.in > output.out
```
## Testing & Validation

Validation is performed with Valgrind to ensure memory safety:
```bash
valgrind --leak-check=full -q --error-exitcode=1 ./set_simulator < input.in
```

Output correctness is checked using diff:
```bash
./set_simulator < example.in | diff - example.out
```
