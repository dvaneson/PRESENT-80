CC = gcc -g

all: present.a block_cipher.a test_present cipher

present.a: present.o
	ar rcs $@ $^

present.o: present.c  present.h
	$(CC) -c -o $@ $<

block_cipher.a: block_cipher.o present.o
	ar rcs $@ $^

block_cipher.o: block_cipher.c block_cipher.h present.h
	$(CC) -c $< -o $@

cipher: cipher.o present.h present.a block_cipher.h block_cipher.a
	$(CC) $^ -o $@

cipher.o: cipher.c present.h block_cipher.h
	$(CC) -c $< -o $@

test_present: test_present.o present.a block_cipher.a
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
