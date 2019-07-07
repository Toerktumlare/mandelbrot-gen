#include <cstdlib>
#include <iostream>
#include <complex>


#define cimg_use_png
#define cimg_display 0

#include "CImg.h"
#include "ArgUtils.h"

using namespace cimg_library;

//65536, 36864

const char CMD_ARG_HEIGHT = 'h';
const char CMD_ARG_WIDTH = 'w';
const char CMD_ARG_FILENAME = 'f';

std::string filename = "default.png";
const int MAX_ITER = 120;
unsigned int WIDTH = 0;
unsigned int HEIGHT = 0;
const int DEPTH = 1;
const int COLOR_SPECTRUM = 3;

const int RE_START = -2;
const int RE_END = 1;
const int IM_START = -1;
const int IM_END = 1;

double mandelbrot(const std::complex<double> &value) {
    std::complex<double> z(0, 0);
    int n = 0;
    while (norm(z) <= 4 && n < MAX_ITER){
        z = (z * z) + value;
        n += 1;
    }
    
    if(n == MAX_ITER) {
        return n;
    }
    
    return n + 1 - std::log2(log(norm(z)) * 0.5);
}

static void show_usage()
{
    std::cerr << "Mandelbrot generator usage:\n"
        << "\tUsage: mandelbrot-gen [options...]\n"
        << "\texample: mandelbrot-gen -w640 -h400 -ftest.png\n"
        << "Options:\n"
        << "\t-h\t Help menu\t\t\t\tShow this help message\n"
        << "\t-h\t HEIGHT<required>\t\tSet image height\n"
        << "\t-w\t WIDTH<required>\t\tSet image width\n"
        << "\t-f\t filename\t\t\t\tSet filename\n"
        << std::endl;
}

static int resolveArgs(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        char c = arg.at(1);
        
        switch(c) {
            case CMD_ARG_HEIGHT: {
                const std::string height = ArgUtils::extractValue(arg);
                
                if(ArgUtils::isNumber(height)) {
                    HEIGHT = std::stoi(height);
                } else {
                    std::cerr << "ERROR: " << height << " is not a positiv number." << std::endl;
                    return 1;
                }
                break;
            }
            case CMD_ARG_WIDTH: {
                const std::string width = ArgUtils::extractValue(arg);

                if(ArgUtils::isNumber(width)) {
                    WIDTH = std::stoi(width);
                } else {
                    std::cerr << "ERROR: " << width << " is not a positiv number." << std::endl;
                    return 1;
                }
                break;
            }
            case CMD_ARG_FILENAME: {
                filename = ArgUtils::extractValue(arg);
                break;
            }
            default:
                return 1;
        }
    }
    
    if(WIDTH == 0 || HEIGHT == 0) {
        std::cerr<< "ERROR: You must set width and height" << std::endl;
        return 1;
    }
    
    return 0;
}

void printProperties() {
    std::cout << "Set properties:Starting image generation" << std::endl;
    std::cout << "\t Dimensions:" << std::endl;
    std::cout << "\t\t Height: " << HEIGHT << std::endl;
    std::cout << "\t\t Width: " << WIDTH << std::endl;
    std::cout << "\t\t Filename: " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    
    if(argc <= 1 || resolveArgs(argc, argv) == 1) {
        show_usage();
        return 1;
    }
    
    printProperties();
    
    std::cout << "<#value#>" << std::endl;
    CImg<float> img(WIDTH, HEIGHT, DEPTH, COLOR_SPECTRUM, 0);
    
    int percentage = 0;
    long i = 0;
    cimg_forXY(img, x, y) {
        std::complex<double> complex(RE_START + ((double)x / WIDTH) * (RE_END - RE_START),
                                     IM_START + ((double)y / HEIGHT) * (IM_END - IM_START));
        double m = mandelbrot(complex);
        
        double color[] = {
            360.0 * m / MAX_ITER,
            1.0,
            (m < MAX_ITER) ? 1.0 : 0
        };
        
        img.draw_point(x, y, color);
        
        if(i % (HEIGHT * WIDTH / 100) == 0) {
            std::cout << percentage << "%" << std::endl;
            percentage += 1;
        }
        
        i++;
    }
    std::cout << "Saving file " << filename << std::endl;
    img.HSVtoRGB()
        .normalize(0, 255)
        .save_png(filename.c_str());
    
    return 0;
}
