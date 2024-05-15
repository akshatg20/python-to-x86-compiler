# Python Compiler

This is the repository to store source code for python compilation toolchain build as a graded course project of CS335 - Compiler Design under the guidance of Prof. Swarnendu Biswas of CSE, IIT Kanpur.

For building this repository follow these steps
```
cd src                                         # Go the the source code directory
make all                                       # Run the Makefile to compile the toolchain
./cs335 --help                                 # Get information about the functioning of the compiler
./cs335 --input <path to input file>           # Check compilation of .py input file.
make clean                                     # Clean all the compiled binaries
```

For more specific output you can also run the following commands
```
# Give input directly from the terminal. You may have to use --verbose or --full to display debug output.
# The output assembly will be stored in a .s file in the same directory.
./cs335

# Redirect x86 assembly output to an output file.
./cs335 --input <path to input file> --output <path to output file> --verbose
./cs335 --input <path to input file> --output <path to output file> --full

# Get detailed debug outputs for the compilation process using --verbose flag.
# Optionally you can set the --debug flag to get all the debug output in a specific file.
./cs335 --input <path to input file> --verbose
./cs335 --input <path to input file> --verbose --debug <path to debug output file>

# In case more detailed debug output is required then --full flag can be used.
# CAUTION : This may potentially print a lot of unnecessary statements as well.
./cs335 --input <path to input file> --full
./cs335 --input <path to input file> --full --debug <path to debug output file>
```

For intermediate outputs like the AST or Parse Tree generated during compilation or 3AC IR or the Symbol Tables can also be dumped using the following methodology
```
# Generate AST pdf and DOT script for the input program
./cs335 --input <path to input file> --dot <path to store dot script>
./cs335 --input <path to input file> --ast <path to store pdf file for AST>
./cs335 --input <path to input file> --dot <path to store dot script> --ast <path to store pdf file for AST>

# Generate Parse Tree pdf for the input program using --parse flag
./cs335 --input <path to input file> --parse <path to store pdf file for AST>
# Generate Symbol Table for input program using --symbol flag
./cs335 --input <path to input file> --symbol <path to directory to store symbol tables>
# Generate 3AC output file using --3ac flag
./cs335 --input <path to input file> --3ac <path to text file to store 3AC>
```

Error dumping during the compilation process
```
# In cases of error the compiler dumps the error generated to the standard error file.
# However, that can also be redirected using --error flag
./cs335 --input <path to input file> --error <path to error file>
```

Group Number - 10
Group Members
Akshat Gupta (200085) \\
Devansh Kumar Jha (200318) \\
Shashwat Gupta (200923) \\
