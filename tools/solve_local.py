#!/usr/bin/env python3
"""Local regression helper for the archived VOCAEND solve path."""

from __future__ import annotations

import os
import pty
import select
import subprocess
import sys
import time
from errno import EIO
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DATA = ROOT / "data"
FLAG = "hzlt{local-regression}"
MELODY = "notflag{I_won't_stop_singing_my_heart_out}"


def read_until(fd: int, marker: bytes, timeout: float = 10.0) -> bytes:
    deadline = time.monotonic() + timeout
    output = bytearray()

    while marker not in output:
        remaining = deadline - time.monotonic()
        if remaining <= 0:
            raise TimeoutError(f"timed out waiting for {marker!r}")

        ready, _, _ = select.select([fd], [], [], remaining)
        if not ready:
            continue

        chunk = read_chunk(fd)
        if not chunk:
            break
        output.extend(chunk)

    return bytes(output)


def read_chunk(fd: int) -> bytes:
    try:
        return os.read(fd, 4096)
    except OSError as exc:
        if exc.errno == EIO:
            return b""
        raise


def send(fd: int, text: str) -> None:
    os.write(fd, text.encode())


def main() -> int:
    (DATA / "flag").write_text(f"{FLAG}\n", encoding="utf-8")

    master, slave = pty.openpty()
    env = os.environ.copy()
    env["VOCA_FAST"] = "1"

    proc = subprocess.Popen(
        ["./vocaend"],
        cwd=DATA,
        env=env,
        stdin=slave,
        stdout=slave,
        stderr=slave,
        close_fds=True,
    )
    os.close(slave)

    transcript = bytearray()

    try:
        transcript.extend(read_until(master, b"OLD TUNES"))
        send(master, "anything\n")

        transcript.extend(read_until(master, b"THIS SONG"))
        send(master, "\n")

        transcript.extend(read_until(master, b"archive index"))
        send(master, "-1\n")

        transcript.extend(read_until(master, MELODY.encode()))
        transcript.extend(read_until(master, b"Verify > "))
        send(master, f"{MELODY}\n")

        transcript.extend(read_until(master, b"Sing your prayer > "))
        send(master, "hello\n")

        transcript.extend(read_until(master, b"last wish"))
        send(master, "; cat flag\n")

        while proc.poll() is None:
            ready, _, _ = select.select([master], [], [], 1.0)
            if ready:
                transcript.extend(read_chunk(master))

        while True:
            ready, _, _ = select.select([master], [], [], 0.1)
            if not ready:
                break
            chunk = read_chunk(master)
            if not chunk:
                break
            transcript.extend(chunk)
    finally:
        os.close(master)

    text = transcript.decode(errors="replace")
    sys.stdout.write(text)

    if FLAG not in text:
        print("solve regression failed: flag was not printed", file=sys.stderr)
        return 1

    return proc.returncode or 0


if __name__ == "__main__":
    raise SystemExit(main())
