#About the Compiler

viperc is the command used to compile a vpr file

# Stages of viper compilation

### 1. Lexical Analysis
##### VL "source.vpr"
### 2. Parsing (Syntax Analysis)
##### VP "symbolTable.vpr"
### 3. Semantic Analysis
#### 3.1 Variable Checking
##### VV "symbolTable.vpr"
#### 3.2 Type Checking
##### VS "PARSETREE.TXT"

## Test Programs
please use prefix "t" to vpr files if you will add a test program for modular testing of the compiler

eg.

tifelse.vpr

tarithmetic.vpr


## Complete Programs
please use prefix "f" to vpr files if you will add a test program for modular testing of the compiler

eg.

fprices.vpr

fcashregister.vpr


#VIPER ISSUES
### Parser - error productions for the ff.
FOR_ARG

RETURNS
