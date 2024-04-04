# Python Compiler

This is the repository to store source code for python compilation toolchain build as a graded course project of CS335 - Compiler Design under the guidance of Prof. Swarnendu Biswas of CSE, IIT Kanpur.

For building this repository follow these steps
```
cd ../src                                      # Go the the source code directory
make all                                       # Run the Makefile to compile the toolchain
./cs335 --help                                 # Get information about the functioning of the compiler
./cs335 --input <path to input file>           # Check compilation of .py input file.
make clean                                     # Clean all the compiled binaries
```

For more specific output you can also run the following commands
```
# Give input directly from the terminal. You may have to use --verbose or --full to display debug output.
./cs335

# Redirect debug outputs to the output file.
./cs335 --input <path to input file> --output <path to output file> --verbose
./cs335 --input <path to input file> --output <path to output file> --full

# Generate AST pdf and DOT script for the input program
./cs335 --input <path to input file> --dot <path to store dot script>
./cs335 --input <path to input file> --ast <path to store pdf file for AST>
./cs335 --input <path to input file> --dot <path to store dot script> --ast <path to store pdf file for AST>
```

Group Number - 10

Group Members

Akshat Gupta (200085)

Devansh Kumar Jha (200318)

Shashwat Gupta (200923)
