all:
	g++ -std=c++11  main.cpp biggest-divisible-conglomerate.cpp -o bdc

run:
	./bdc

try: all run