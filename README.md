# 101 - Corrected

This corrected package replaces the OS-lab code found in the uploaded cheat101 ZIP with C solutions for the **Simulation Lab Question Archive**.

## Files

- `run.sh` — main Bash-array solution file
- `WAYLAND_C_SRC` — same source script, kept to match the uploaded ZIP structure
- `WAYLAND_C_BIN` — executable script wrapper, kept to match the uploaded ZIP structure
- `solutions/` — all 25 extracted `.c` files

## Usage

```bash
chmod +x run.sh
./run.sh --list
./run.sh -n 1 -p 100 -r
./run.sh --write-all
```

After extracting a solution, compile it using the command shown by `-r`, for example:

```bash
gcc q01_dump_truck_probability.c -o q01 && ./q01
```

For programs using `math.h`, add `-lm`:

```bash
gcc q02_table_2_4_metrics.c -lm -o q02 && ./q02
```

## Validation

All 25 generated C files were syntax-checked by compiling with `gcc`. Programs using `sqrt()`/math functions were compiled with `-lm`.
# 101-corrected
