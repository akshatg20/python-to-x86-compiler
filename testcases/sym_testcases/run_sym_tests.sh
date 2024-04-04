#!/bin/bash

# This is a Bash script that runs the lexer and parser together

# Source folder containing input testcases
source_folder="../testcases/sym_testcases"
# Destination folder for output of testcases from parser
root_folder="../output"
sym_folder="../output/sym_cases"
intermediate_folder="../output/sym_cases/dot"
destination_folder1="../output/sym_cases/ast"
destination_folder2="../output/sym_cases/parse"
destination_folder3="../output/sym_cases/symbol"

# Change the current directory and setup the source code
cd ../../src
make all

# Loop through each file in the testcases folder and generate the AST and DOT files
mkdir -p "$root_folder"
mkdir -p "$sym_folder"
mkdir -p "$intermediate_folder"
mkdir -p "$destination_folder1"
mkdir -p "$destination_folder2"
mkdir -p "$destination_folder3"
for file in "$source_folder"/*; do
    if [ -f "$file" ]; then
        filename=$(basename -- "$file")
        filename_no_ext="${filename%.*}"
        extension="${file##*.}"
        if [ "$extension" = "py" ]; then
            ./cs335 --input "$file" --ast "$destination_folder1/$filename_no_ext.pdf"
            ./cs335 --input "$file" --dot "$intermediate_folder/$filename_no_ext.dot" --parse "$destination_folder2/$filename_no_ext.pdf" --symbol "$destination_folder3/$filename_no_ext"
        fi
    fi
done

# Return back to the original directory
cd ../testcases/sym_testcases
