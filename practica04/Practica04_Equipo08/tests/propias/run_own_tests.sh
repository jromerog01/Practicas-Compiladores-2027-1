#!/bin/sh



set -u

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
executable=${1:-./minic}
expected_ok="Programa sintacticamente correcto."

passed=0
failed=0

for input in "$script_dir"/validos/*.mc; do
    name=$(basename "$input" .mc)
    out=$("$executable" "$input" 2>/tmp/minic_err_$$)
    status=$?

    if [ "$status" -eq 0 ] && [ "$out" = "$expected_ok" ] \
       && [ ! -s /tmp/minic_err_$$ ]; then
        passed=$((passed + 1))
    else
        printf '[FALLO] %s\n' "$name"
        failed=$((failed + 1))
    fi
done

for input in "$script_dir"/invalidos/*.mc; do
    name=$(basename "$input" .mc)
    out=$("$executable" "$input" 2>/tmp/minic_err_$$)
    status=$?

    if [ "$status" -eq 1 ] && [ -z "$out" ] \
       && [ "$(cat /tmp/minic_err_$$)" = "$(cat "${input%.mc}.err")" ]; then
        passed=$((passed + 1))
    else
        printf '[FALLO] %s\n' "$name"
        failed=$((failed + 1))
    fi
done

rm -f /tmp/minic_err_$$

printf 'Propias: %s aprobadas, %s fallidas\n' "$passed" "$failed"
[ "$failed" -eq 0 ]
