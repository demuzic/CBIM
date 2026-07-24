#pragma once
#include "image.h"
#include <vector>
#include <string>

struct Kernel {
    int width;
    int height;
    std::vector<std::vector<float>> data;
};

Kernel load_kernel(const std::string& kernel_name);
Kernel make_kernel(int width, int height);
Image apply_kernel(const Image& img, const Kernel& k);
