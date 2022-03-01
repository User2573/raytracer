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

Image::Image(const int _side) : Image(_side, _side) {}

Image::Image(const int _width, const int _height) : width(_width), height(_height)
{
	data.resize(width * height);
}



const Color& Image::operator () (const int x, const int y) const
{
	return data.at(x + y*width);
}

Color& Image::operator () (const int x, const int y)
{
	return data.at(x + y*width);
}



void Image::for_each(const std::function<void(Color&, int, int)>& lambda)
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			lambda(data.at(x + y*width), x, y);
		}
	}
}

template <class ExecutionPolicy>
void Image::for_each(ExecutionPolicy policy, const std::function<void(Color&, int, int)>& lambda)
{
	std::for_each(
		policy,
		data.begin(),
		data.end(),
		[&lambda](Color& color) {
			lambda(color, 0, 0);
		}
	);
}

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
	std::string command = "ffmpeg -loglevel quiet -y -i ";
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
			ss << "\033[0m";
			pcol = &data.at(x + y*width); // top color
			ss << "\033[48:2:" << int(std::clamp(pcol->r, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->g, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->b, 0.0, 1.0)*255) << "m";
			pcol = &data.at(x + (y-1)*width); // bottom color
			ss << "\033[38:2:" << int(std::clamp(pcol->r, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->g, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->b, 0.0, 1.0)*255) << "m";
			ss << "\u2585"; // lower five-eights box character
		}
		ss << std::endl;
	}
//	ss << "\033[0m\033[?25h";

	return ss.str();
}
