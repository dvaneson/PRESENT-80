CC = gcc -g

all: present.a present.o test_present cipher

present.a: present.o
	ar rcs $@ $^

present.o: present.c  present.h
	$(CC) -c -o $@ $< -lm

cipher: cipher.o present.h present.a
	$(CC) $^ -o $@ -lm

cipher.o: cipher.c present.h
	$(CC) -c $< -o $@ -lm

test_present: test_present.o present.h present.a
	$(CC) $^ -o $@ -lm

test_present.o: test_present.c present.h
	$(CC) -c $< -o $@ -lm

clean:
	rm -f *.o *.a core

test: present.a present.o test_present
	./test_present

encrypt: present.a present.o cipher
	./cipher encrypt

decrypt: present.a present.o cipher
	./cipher decrypt
