all: compile open

compile:
	g++ hanoi.cpp -o hanoi.exe

open: 
	./hanoi.exe