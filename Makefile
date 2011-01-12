scr = main.c basic_shape.c board.c
para  = -Wall


main:$(scr)
	gcc -o main $(scr)  $(para)
clean :
	-rm -rf main
	-rm -rf *.o
	-rm -rf *~
	-rm -rf a.out
