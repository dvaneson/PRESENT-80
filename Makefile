CC = gcc -g

all: present.a present.o test_present.exe present_demo.exe

present.a: present.o
	ar rcs $@ $^

present.o: present.c  present.h
	$(CC) -c -o $@ $< -lm

test_present.exe: test_present.o present.h present.a
	$(CC) $^ -o $@ -lm

test_present.o: test_present.c present.h
	$(CC) -c $< -o $@ -lm

clean:
	rm -f *.o *.a core

run: all
	./test_present.exe

demo: all
	./present_demo.exe
