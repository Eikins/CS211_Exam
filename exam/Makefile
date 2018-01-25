laby: laby.o main.o
	gcc -Wall -g -o $@ $^

%.o: %.c
	gcc -Wall -g -c $<

clean:
	rm -rf *.o
	rm -rf ./laby
