aSTbc: Key.o Note.o Print_Visitor.o Visitor.o rational.o StringFunctions.o aSTbc.y.o aSTbc.l.o commander.o
	g++ Key.o Note.o Print_Visitor.o Visitor.o rational.o StringFunctions.o aSTbc.y.o aSTbc.l.o commander.o -o aSTbc

Key.o: Key.cpp
	g++ -c Key.cpp

Note.o: Note.cpp
	g++ -c Note.cpp

Print_Visitor.o: Print_Visitor.cpp
	g++ -c Print_Visitor.cpp

Visitor.o: Visitor.cpp
	g++ -c Visitor.cpp

rational.o: rational.cpp
	g++ -c rational.cpp

StringFunctions.o: StringFunctions.cpp
	g++ -c StringFunctions.cpp

aSTbc.y.o: aSTbc.y.c
	g++ -c aSTbc.y.c

aSTbc.l.o: aSTbc.l.c
	g++ -c aSTbc.l.c

aSTbc.y.c: aSTbc.y
	yacc --defines=aSTbc.h -o aSTbc.y.c aSTbc.y

aSTbc.l.c: aSTbc.l
	lex -o aSTbc.l.c aSTbc.l

commander.o: commander.cpp
	g++ -c commander.cpp

clean:
	rm aSTbc Key.o Note.o Print_Visitor.o Visitor.o rational.o StringFunctions.o aSTbc.y.o aSTbc.l.o commander.o aSTbc.y.c aSTbc.l.c
