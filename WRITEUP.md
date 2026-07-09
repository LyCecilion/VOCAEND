# VOCAEND Writeup

VOCAEND was made for hzlt!Game 2026 as a story-first entertainment challenge.
The published source intentionally keeps the old competition mechanics,
including the misleading constructor entrypoint and the unsafe operations used
by the solve path.

## Intended Path

1. Run the binary from `data/` so the `song*.txt` files are in the working
   directory.
2. Enter anything for `OLD TUNES`.
3. Leave `THIS SONG` empty. This triggers the emergency recovery signal path.
4. Select archive index `-1`.
5. The negative archive index intentionally reads `song11.txt` through the
   database layout and prints the hidden melody.
6. Enter that printed melody at `Verify >`.
7. Enter anything at `Sing your prayer >`.
8. At `Any last wish before shutdown, Master? ... >`, enter `; cat flag`.

The final command is built as `ping <last wish>`, so the leading semicolon
starts a second shell command and prints the flag file.

## Design Notes

- `src/protocol.c` owns the real challenge flow. It uses a constructor so the
  decoy `main()` is not normally reached.
- `src/main.c` is a deliberate decoy path. It should remain buildable, but the
  constructor exits before it in normal execution.
- `song0.txt` through `song10.txt` are community/callback archive entries.
- `song11.txt` is the hidden melody used by the recovery verification step.
- The negative index, format string echo, and shell command construction are
  intentionally preserved as part of the original solve chain.

## Local Reproduction

```sh
make
echo 'flag{test}' > data/flag
cd data
VOCA_FAST=1 ./vocaend
```

Send inputs interactively rather than piping the whole solve transcript at once.
The original `read(2)` calls can consume more than one line if all input is
provided in a single pipe.
