CC = gcc -g

all: present.a present.o test_present

present.a: present.o
	ar rcs $@ $^

present.o: present.c  present.h
	$(CC) -c -o $@ $< -lm

test_present: test_present.o present.h present.a
	$(CC) $^ -o $@ -lm

test_present.o: test_present.c present.h
	$(CC) -c $< -o $@ -lm

clean:
	rm -f *.o *.a core

test: present.a present.o test_present
	./test_present
