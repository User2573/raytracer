linkTarget = raytracer.out



# no -Wpedantic because math/vector.hpp uses anonymous structs
CFLAGS = -std=c++17 -Wall -Wextra #-Wpedantic

objects = main.o \
          $(patsubst %.cpp,%.o,$(wildcard ./**/*.cpp))

rebuildables = $(objects) $(linkTarget)



$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(CFLAGS)

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)



.PHONY: clean

clean:
	rm $(rebuildables)
