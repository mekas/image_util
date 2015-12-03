run : main.o
	gcc -o main main.o `pkg-config --libs glib-2.0 MagickWand`

main.o : main.c 
	gcc -c `pkg-config --cflags glib-2.0 MagickWand` main.c

clean :
	rm main main.o
