CC = gcc -g

all: present.a present.o test_present cipher

present.a: present.o
	ar rcs $@ $^

present.o: present.c  present.h
	$(CC) -c -o $@ $<

cipher: cipher.o present.h present.a
	$(CC) $^ -o $@

cipher.o: cipher.c present.h
	$(CC) -c $< -o $@

test_present: test_present.o present.h present.a
	$(CC) $^ -o $@ -lbsd

test_present.o: test_present.c present.h
	$(CC) -c $< -o $@ -lbsd

clean:
	rm -f *.o *.a core cipher test_present

test: present.a present.o test_present
	./test_present

encrypt: present.a present.o cipher
	./cipher encrypt

decrypt: present.a present.o cipher
	./cipher decrypt
