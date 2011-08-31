
OBJ = unpack.o

%.o: %.c
	gcc -c $< -o $@

unpack: $(OBJ)
	gcc $< -o $@

clean:
	rm -f *.o unpack
