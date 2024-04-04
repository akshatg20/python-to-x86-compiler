# Compilation softwares
CC = g++
LEX = flex
YACC = bison
CFLAGS =
YFLAGS = -d
LFLAGS =

# Source files
LEX_FILE = scan.l
YACC_FILE = parse.y
MAIN_FILE = main.cpp

# Output files
LEX_OUTPUT = lex.yy.c
YACC_OUTPUT = parse.tab.c
YACC_HEADER = parse.tab.h
OUTPUT = cs335

# ```Make all``` program
all: $(OUTPUT)

$(LEX_OUTPUT): $(LEX_FILE)
	$(LEX) $(LFLAGS) -o $(LEX_OUTPUT) $(LEX_FILE)

$(YACC_OUTPUT): $(YACC_FILE)
	$(YACC) $(YFLAGS) -o $(YACC_OUTPUT) $(YACC_FILE)

$(OUTPUT): $(LEX_OUTPUT) $(YACC_OUTPUT) $(MAIN_FILE)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(LEX_OUTPUT) $(YACC_OUTPUT) $(MAIN_FILE)

# ```Make clean``` program
clean:
	rm -f $(LEX_OUTPUT) $(YACC_OUTPUT) $(YACC_HEADER) $(OUTPUT)
