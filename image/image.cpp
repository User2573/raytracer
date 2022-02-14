#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include "fcolor.hpp"
#include "../math/vector.hpp"
#include "image.hpp"



Image::Image() : Image(128, 128) {}

Image::Image(int _side) : Image(_side, _side) {}

Image::Image(int _width, int _height) : width(_width), height(_height)
{
	data.resize(width * height);
}



const Color& Image::operator () (int x, int y) const
{
	return data.at(x + y*width);
}

Color& Image::operator () (int x, int y)
{
	return data.at(x + y*width);
}



void Image::for_each(std::function<void(Color&, int, int)> lambda)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			lambda(data.at(x + y*width), x, y);
		}
	}
}

//void Image::for_each(std::execution::policy policy, std::function<void(Color&, int, int)> lambda)


void Image::writeToPPM(const char* filename) const
{
	std::ofstream ofs(filename, std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			ofs << FColor{data.at(x + y*width)};
		}
	}
	ofs.close();
}

void Image::writeToPNG(const char* filename) const
{
	std::string ppmname = filename;
	ppmname += ".ppm";
	writeToPPM(ppmname.c_str());
	std::string command = "ffmpeg -loglevel quiet -i ";
	command += ppmname;
	command += " ";
	command += filename;
	system(command.c_str());
	std::string remove = "rm ";
	remove += ppmname;
	system(remove.c_str());
}

std::string Image::str() const
{
	std::stringstream ss;
	const Color* pcol = nullptr;
	for (int y = height - 1; y >= 0; y -= 2) {
		for (int x = 0; x < width; ++x) {
			ss << "\e[m";
			pcol = &data.at(x + y*width); // top color
			ss << "\e[48:2:" << int(std::clamp(pcol->r, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->g, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->b, 0.0, 1.0)*255) << "m";
			pcol = &data.at(x + (y-1)*width); // bottom color
			ss << "\e[38:2:" << int(std::clamp(pcol->r, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->g, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->b, 0.0, 1.0)*255) << "m";
			ss << "\u2585"; // lower five-eights box character
		}
		ss << std::endl;
	}
//	ss << "\e[m\e[?25h";

	return ss.str();
}
