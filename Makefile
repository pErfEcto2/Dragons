build:
	g++ -c sprite.cpp
	g++ sprite.o -o app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio