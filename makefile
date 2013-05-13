RM         = rm -f
LEXER_GEN  = flex
PARSER_GEN = bison

objects = lexer.o parser.o expression.o
depend  = parser.h lexer.h expression.h

# Ignore make's built in yacc and lex rules.
%.c: %.y 
%.c: %.l 

%.o: %.c $(depend)
	$(CC) -c -o $@ $< $(CFLAGS)

all: fe

.phony: all clean

lexer.c lexer.h: lexer.l
	$(LEXER_GEN) $<

parser.c parser.h: parser.y
	$(PARSER_GEN) $<

fe: ferrous.c $(objects)
	$(CC) $^ -o $@

clean:
	$(RM) *.o
	$(RM) lexer.c
	$(RM) parser.c
	$(RM) lexer.h
	$(RM) parser.h
	$(RM) fe

