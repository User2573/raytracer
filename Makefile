linkTarget = raytracer.out



CFLAGS = -std=c++17 -Wall -Wextra -Wpedantic



rebuildables = $(objects) $(linkTarget)

headers = $(patsubst

$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(CFLAGS)

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)



.PHONY: clean

clean:
	rm $(rebuildables)
