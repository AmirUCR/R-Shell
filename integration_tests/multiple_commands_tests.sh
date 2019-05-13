#!/bin/sh

echo "echo hi && ls -a && INVALIDCMD || echo bye; git status" | ../src/a.out > multiple_command_tests_output.txt