linkTarget = raytracer



LIBS = -lSDL2

CFLAGS = -std=c++17

objects = main.o \
          app.o \
          $(patsubst %.cpp,%.o,$(wildcard ./raytracing/*.cpp))

rebuildables = $(objects) $(linkTarget)



$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)



.PHONY: clean

clean:
	rm $(rebuildables)
