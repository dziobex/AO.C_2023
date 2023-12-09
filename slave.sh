#!/bin/bash

# usuwa .exe-ki i pliki input wziete ze strony https://adventofcode.com/2023
# nastepnie automatycznie wstawia wszystkie zmiany na moje zdalne repo

find . -name "*.exe" -exec rm '{}' \;
find . -type f \( -name "in.txt" -o -name "input.txt" \) -exec rm '{}' \;

if [ "$#" -ne 1 ]; then
    echo ":("
    exit 1
fi

git add .
git commit -m "$1"
git push