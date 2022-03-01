linkTarget = a.out



# no -Wpedantic because math/vector.hpp uses anonymous structs
CFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic

headers = renderer.hpp.gch \
          $(patsubst %.hpp,%.hpp.gch,$(wildcard ./**/*.hpp))

objects = main.o \
          renderer.o \
          $(patsubst %.cpp,%.o,$(wildcard ./**/*.cpp))

rebuildables = $(headers) $(objects) $(linkTarget)



$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(CFLAGS)
	ls

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

$(headers): %.hpp
	g++ $< $(CFLAGS)



.PHONY: clean rmo

rmo: # remove output
	rm output.png a.out

clean:
	rm $(rebuildables) *.png *.ppm
