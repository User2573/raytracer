#include <algorithm>
#include <cstdlib>
#include <execution>
#include <fstream>
#include <functional>
#include <ranges>
#include <sstream>
#include <string>
#include "../math/vector.hpp"
#include "pixel.hpp"
#include "image.hpp"



Image::Image() : Image(256, 256) {}

Image::Image(const int _side) : Image(_side, _side) {}

Image::Image(const int _width, const int _height) : width(_width), height(_height)
{
	data.resize(width * height);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int i = x + y * width;
			data.at(i).x = x;
			data.at(i).y = y;
		}
	}
}



const Color& Image::operator () (const int x, const int y) const
{
	return data.at(x + y*width).value;
}

Color& Image::operator () (const int x, const int y)
{
	return data.at(x + y*width).value;
}

void Image::for_each(const std::function<void(Color&, int, int)>& lambda)
{
	std::for_each(
		std::execution::par_unseq,
		data.begin(),
		data.end(),
		[&](Pixel& pixel) {
			lambda(pixel.value, pixel.x, pixel.y);
		}
	);
}

void Image::writeToPPM(const char* filename) const
{
	std::ofstream ofs(filename, std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			ofs << data.at(x + y*width);
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
			pcol = &data.at(x + y*width).value; // top color
			ss << "\033[48:2:" << int(std::clamp(pcol->r, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->g, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->b, 0.0, 1.0)*255) << "m";
			pcol = &data.at(x + (y-1)*width).value; // bottom color
			ss << "\033[38:2:" << int(std::clamp(pcol->r, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->g, 0.0, 1.0)*255)
			          << ":" << int(std::clamp(pcol->b, 0.0, 1.0)*255) << "m";
			ss << "\u2585"; // lower five-eights box character
		}
		ss << "\n";
	}
//	ss << "\033[0m\033[?25h";

	return ss.str();
}
