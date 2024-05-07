#!/bin/bash

# This is a Bash script that runs the complete compiler at once
# Check if no arguments are provided
if [ $# -eq 0 ]; then
    echo "No arguments provided. Please provide at least one argument."
    echo "The arguments supported are 3ac, ast, main, milestone3, public, sym, x86."
    echo "Please give only one argument at a time."
    exit 1
fi

# Check if the first argument is empty
if [ -z "$1" ]; then
    echo "First argument is empty. Please provide a non-empty argument."
    echo "The arguments supported are 3ac, ast, main, milestone3, public, sym, x86."
    echo "Please give only one argument at a time."
    exit 1
fi

# Source folder containing input testcases
source_folder="../testcases/{}_testcases"
source_folder="${source_folder/\{\}/$1}"
# Destination folder for output of testcases from compiler
root_folder="../output/{}_testcases"
root_folder="${root_folder/\{\}/$1}"

# Specific output folders
ast_folder="ast"
ast_dot_folder="ast_dot"
parse_folder="parse"
parse_dot_folder="parse_dot"
symbol_folder="sym"
ac3_folder="3ac"
x86_folder="x86"

# Create directories which are not already present
mkdir -p "$root_folder"
mkdir -p "$root_folder/$ast_folder"
mkdir -p "$root_folder/$ast_dot_folder"
mkdir -p "$root_folder/$parse_folder"
mkdir -p "$root_folder/$parse_dot_folder"
mkdir -p "$root_folder/$symbol_folder"
mkdir -p "$root_folder/$ac3_folder"
mkdir -p "$root_folder/$x86_folder"

# Change the current directory and setup the source code
cd ../src
make all

# Loop through each file in the testcases folder and generate the AST and DOT files

for file in "$source_folder"/*; do
    if [ -f "$file" ]; then
        filename=$(basename -- "$file")
        filename_no_ext="${filename%.*}"
        extension="${file##*.}"
        if [ "$extension" = "py" ]; then
            ./cs335 --input "$file" --dot "$root_folder/$ast_dot_folder/$filename_no_ext.dot" --ast "$root_folder/$ast_folder/$filename_no_ext.pdf"
            ./cs335 --input "$file" --dot "$root_folder/$parse_dot_folder/$filename_no_ext.dot" --parse "$root_folder/$parse_folder/$filename_no_ext.pdf" --symbol "$root_folder/$symbol_folder/$filename_no_ext" --3ac "$root_folder/$ac3_folder/$filename_no_ext.txt" --output "$root_folder/$x86_folder/$filename_no_ext.s"
        fi
    fi
done

# Return back to the original directory
cd ../testcases
