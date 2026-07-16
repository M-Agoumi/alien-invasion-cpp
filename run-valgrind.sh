#!/usr/bin/env bash
# Run AlienInvasion under Valgrind with our suppression file applied so
# that only *real* (our-code) leaks are reported. Third-party X11 / LLVM /
# dynamic-loader init allocations are suppressed via valgrind.supp.
#
# Usage:
#   ./run-valgrind.sh                 # normal, suppressed run
#   ./run-valgrind.sh --gen           # regenerate raw suppressions (no filtering)
set -euo pipefail

# Always run from the project root (so resource paths + supp file resolve)
cd "$(dirname "$0")"

BIN="./build/AlienInvasion"
SUPP="valgrind.supp"

if [[ ! -x "$BIN" ]]; then
  echo "error: $BIN not found or not executable. Build first, e.g.:" >&2
  echo "  cmake -S . -B build && cmake --build build" >&2
  exit 1
fi

if [[ "${1:-}" == "--gen" ]]; then
  # Print raw suppression blocks for any leaks NOT already covered,
  # so you can paste new ones into valgrind.supp.
  exec valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --suppressions="$SUPP" \
    --gen-suppressions=all \
    "$BIN"
fi

exec valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  --error-exitcode=1 \
  --suppressions="$SUPP" \
  "$BIN"

