#!/bin/sh

echo "echo hi && ls -a && INVALIDCMD || echo bye; git status; exit" | ../rshell > multiple_command_tests_output.txt