#!/bin/sh

echo "(echo A && echo B) || (echo C && echo D); exit" | ../rshell >> precedence_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> precedence_tests_output.txt
echo "((echo A && echo B) || (echo C && echo D) && (echo E && echo F) || (echo G && echo H)); exit" | ../rshell >> precedence_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> precedence_tests_output.txt
echo "(echo Hello && (echo Bonjour; echo Aloha! || echo Ciao)); exit" | ../rshell >> precedence_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> precedence_tests_output.txt
echo '(echo "Ann)yeong!" || echo Au revoir!) && echo "(Addio!)"; exit' | ../rshell >> precedence_tests_output.txt
echo "echo ------------------------------------------; exit" | ../rshell >> precedence_tests_output.txt
echo "(echo \"Grazie #;;||signore!\" || echo Danke Schoen!; echo Moteshakeram!) && echo \"(Merci beaucoup)\"; exit" | ../rshell >> precedence_tests_output.txt
