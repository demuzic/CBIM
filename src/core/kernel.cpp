#include "../../include/core/kernel.h"
#include "../../include/core/image.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

Kernel load_kernel(const string& kernel_name) {
    ifstream archive(kernel_name);
    if(!archive.is_open()) return {};
    int u, v;
    archive >> v >> u;
    Kernel k;
    k.width = u;
    k.height = v;
    k.data = vector<vector<float>>(v, vector<float>(u));
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < u; j++) {
            archive >> k.data[i][j];
        }
    }
    return k;
}

Kernel make_kernel(int width, int height) {
    Kernel k;
    k.width = width;
    k.height = height;
    k.data.resize(height);
    for (int i = 0; i < height; i++) {
        k.data[i].resize(width);
    }
    for (int v = 0; v < height; v++) {
        for (int u = 0; u < width; u++) {
            cout << u + 1 << "x" << v + 1 << ": " << endl;
            cin >> k.data[v][u];
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return k;
}

Image apply_kernel(const Image& img, const Kernel& k, int flag) { //flag: -1 = all rgb layers, 0 = r, 1 = g and 2 = b
    Image new_img;
    new_img.width = img.width;
    new_img.height = img.height;
    new_img.maxVal = img.maxVal;
    new_img.data.resize(img.height, vector<Pixel>(img.width, {0,0,0}));
    int h_offset = k.width / 2;
    int v_offset = k.height / 2;
    for (int i = 0; i < new_img.height; i++) {
        for (int j = 0; j < new_img.width; j++) {
            float sumR = 0, sumG = 0, sumB = 0;
            for(int v = 0; v < k.height; v++) {
                for(int u = 0; u < k.width; u++) {
                    int iy = i + v - v_offset;
                    int ix = j + u - h_offset;
                    if (iy < 0) iy = 0;
                    else if (iy >= img.height) iy = img.height - 1;
                    if (ix < 0) ix = 0;
                    else if (ix >= img.width) ix = img.width - 1;
                    if (flag == -1 || flag == 0 )sumR += k.data[v][u] * img.data[iy][ix].r;
                    if (flag == -1 || flag == 1 )sumG += k.data[v][u] * img.data[iy][ix].g;
                    if (flag == -1 || flag == 2 )sumB += k.data[v][u] * img.data[iy][ix].b;
                }
            }
            if (flag == -1 || flag == 0 )new_img.data[i][j].r = max(0, min(255, (int)sumR));
            if (flag == -1 || flag == 1 )new_img.data[i][j].g = max(0, min(255, (int)sumG));
            if (flag == -1 || flag == 2 )new_img.data[i][j].b = max(0, min(255, (int)sumB));
        }
    }
    return new_img;
}
