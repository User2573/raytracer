#include <parallel/algorithm>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
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

std::vector<Pixel>::iterator Image::begin()
{ return data.begin(); }

std::vector<Pixel>::iterator Image::end()
{ return data.end(); }

std::vector<Pixel>::const_iterator Image::begin() const
{ return data.cbegin(); }

std::vector<Pixel>::const_iterator Image::end() const
{ return data.cend(); }

std::vector<Pixel>::const_iterator Image::cbegin() const
{ return data.cbegin(); }

std::vector<Pixel>::const_iterator Image::cend() const
{ return data.cend(); }
/*
void Image::for_each(const std::function<Color(Color, int, int)>& lambda)
{
/*	// WOOHOO std::thread spam!
	// create 1 thread for each 16 pixels,
	// have a special thread take care of the remaining pixels
	const int pixperthread = 16;
	const int npix = width * height;
	const int nthreads = npix / pixperthread;
	std::cout << "pix per thread: " << pixperthread << "\n"
	             "n pix         : " << npix << "\n"
				 "n threads     : " << nthreads << "\n";

	std::vector<std::thread> threads;
	threads.reserve(nthreads + 1);
	for (int i = 0; i < nthreads; i += pixperthread) {
		threads.emplace_back([&]() {
			for (int j = 0; j < pixperthread; j++) {
				Pixel& pixel = data.at(i + j);
				lambda(pixel.value, pixel.x, pixel.y);
			}
		});
	}
	threads.emplace_back([&]() {
		std::cout << "last thread" << "\n";
		for (int i = nthreads * pixperthread; i < npix; ++i) {
			std::cout << "last i: " << i << "\n";
			Pixel& pixel = data.at(i);
			lambda(pixel.value, pixel.x, pixel.y);
		}
		std::cout << "end last thread" << "\n";
	});
	
	for (std::thread& t : threads) t.join();
//
//
	__gnu_parallel::for_each(
//		std::execution::par_unseq,
		data.begin(),
		data.end(),
		[&](Pixel& pixel) {
			pixel.value = lambda(pixel.value, pixel.x, pixel.y);
	    }
	);
}*/

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
