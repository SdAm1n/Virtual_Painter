Virtual Painter: main.o
	g++ main.o -o "Virtual Painter" `pkg-config --cflags --libs opencv4`

main.o: main.cpp
	g++ -c main.cpp `pkg-config --cflags --libs opencv4`

clean:
	rm *.o 'Virtual Painter'