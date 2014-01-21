default: run

ex1: ex1.cpp utils.cpp sphere.cpp particle.cpp ex1.h
	g++ -std=c++11 -O3 -fomit-frame-pointer -Wall -pipe -DFX -DXMESA -lGL -lGLU -lglut -lX11 -lm -o ex1 ex1.cpp utils.cpp sphere.cpp particle.cpp

run: ex1
	./ex1