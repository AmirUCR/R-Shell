#!/bin/sh

echo "cat < ../text.txt && (test -f ../text.txt && (echo hello world)); exit" | ../rshell > input_redirection_test_output