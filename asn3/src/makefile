scene = scene/*.hpp scene/*.cpp
shapes = shapes/*.hpp shapes/*.cpp
utils = utils/*.hpp utils/*cpp
graphics = GraphicsWindow.cpp GraphicsWindow.hpp

clean:
	rm -rf a.out

build:
	g++ main.cpp -w ${graphics} ${scene} ${shapes} ${utils} -L/usr/x11R6/lib -lX11 -std=c++11