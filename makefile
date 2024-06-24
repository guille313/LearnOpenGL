main.out: main.cpp glad.c
	c++ -o main.out main.cpp glad.c -lglfw -I include/

run: main.out
	./main.out
