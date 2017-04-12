VIPER LEX 8.7

Viper Lexical Analyzer _ Date Created: 08 / 07 / 2016
-this lexical analyzer produces a symbol table ("symbolTable_" + input_file_name.vpr)

[DIR]
Viper Lexical Analyzer 8.7.c   	= Lexical Analyzer
vlexical.h			= Lexical Header
test.vpr 			= Viper code without error
symbolTable_test.vpr		= Symbol table produced by lexical for test.vpr
d.vpr				= Viper code with error
symbolTable_d.vpr		= Symbol table produced by lexical for d.vpr

-----------------------------
d.vpr ERROR(s)
line 4: "mein"	(main)
line 6: "and"   (end)
-----------------------------