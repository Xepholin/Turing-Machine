##
# Turing Machine
#

objets = convert.o turing.o utilities.o main.o biinfini.o codage.o

run: compile
	./turing -d ./MT/pair 01010 A QACCEPT

test: compile
	./turing -d ./MT/addition 100 A QACCEPT
	./turing -d ./MT/palindrome 10101 A QACCEPT
	./turing -d ./MT/soustraction 1001 A QACCEPT
	./turing -t ./MT/apair
	./turing -d ./MT/new 010101 A Z


compile: $(objets)
	gcc -Wall -o turing $(objets)

clean:
	rm $(objets) turing
	rm MT/new


# end
