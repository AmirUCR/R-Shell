#!/bin/sh

echo "test -f ../text.txt && cat < ../text.txt | sort | tr a-z A-Z; exit" | ../rshell > pipe_operator_test_output