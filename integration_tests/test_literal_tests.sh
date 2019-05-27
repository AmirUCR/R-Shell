#!/bin/sh

echo 'test -d ../header/"this folder does not exist "; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test -d ../header/"new folder"; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test -d ../header/"new folder"/"new new folder"; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test ../rshell && echo "file exists"; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test ../randomrandom; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test -e ../src/execvp.cpp; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test -e ../folder/test; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test -f ../header/"new folder"/"new new folder"; exit' | ../rshell >> test_literal_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> test_literal_tests_output.txt

echo 'test -f ../header/"new folder"/"new new folder"; exit' | ../rshell >> test_literal_tests_output.txt
