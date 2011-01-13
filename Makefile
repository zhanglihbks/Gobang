scr = main.c basic_shape.c board.c draw_chess.c  mouse_shape.c
para  = -Wall


main:$(scr)
	gcc -o main $(scr)  $(para)
clean :
	-rm -rf main
	-rm -rf *.o
	-rm -rf *~
	-rm -rf a.out
	-rm -rf *.gch
