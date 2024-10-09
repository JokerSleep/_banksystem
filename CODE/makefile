bank: main.o bank.o file.o list.o 
	gcc *.o -o $@
%.o:%.c
	gcc -c $< -o $@

clean:
	rm -rf bank *.o