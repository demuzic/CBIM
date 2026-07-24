#pragma once
#include <vector>
#include <string>
#include "pixel.h"

struct Image {
    int maxVal;
    int width;
    int height;
    std::vector<std::vector<Pixel>> data;
};

Image load_image(const std::string& image_name);
void make_ppm(const Image& img, const std::string& filename);
