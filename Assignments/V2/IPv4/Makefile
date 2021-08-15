default: main

main: main.c packets_settings.o
	gcc main.c -o main packets_settings.o
	
packets_settings.o: packets_settings.c packets_settings.h
	gcc -c packets_settings.c
	
clean:
	rm -f *.o main
