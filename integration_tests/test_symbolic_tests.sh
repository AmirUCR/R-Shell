#!/bin/sh

echo '[ -d ../header/"this folder does not exist" ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ -d ../header/"new folder" ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ -d ../header/"new folder"/"new new folder" ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ ../rshell && echo "file exists" ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ ../randomrandom ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ -e ../src/execvp.cpp ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ -e ../folder/test ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ -f ../header/"new folder"/"new new folder" ]; exit' | ../rshell >> test_symbolic_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_symbolic_tests_output.txt

echo '[ -f ../header/"new folder"/"new new folder" ]; exit' | ../rshell >> test_symbolic_tests_output.txt
