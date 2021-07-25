build_sprite:
	g++ -c test.cpp
	g++ test.o -o test -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
build_Dragons:
	g++ -c Dragons.cpp
	g++ Dragons.o -o Dragons -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
build_test_collision:
	g++ -c test_collision.cpp
	g++ test_collision.o -o test_collision -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
