linkTarget = a.out



CFLAGS = -std=c++20 -O2 -Wall -Wextra -Wpedantic -ltbb -fopenmp

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



.PHONY: clean rmout pch

pch:
	g++ stdpch.hpp $(CFLAGS)

rmout: # remove output
	rm output.png a.out

clean:
	rm $(rebuildables) *.png *.ppm
