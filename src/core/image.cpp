#include "../../include/core/image.h"
#include <fstream>
#include <iostream>
#include "../../include/core/pixel.h"
using namespace std;


Image load_image(const string& image_name) {
    ifstream archive(image_name);
    if(!archive.is_open()) return {};
    string type;
    int width, height, maxVal;
    archive >> type >> width >> height >> maxVal;
    Image img;
    img.width = width;
    img.height = height;
    img.maxVal = maxVal;
    img.data = vector<vector<Pixel>>(height, vector<Pixel>(width));
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            archive >> img.data[i][j].r >> img.data[i][j].g >> img.data[i][j].b;
        }
    }
    return img;
}
Image create_image_by_layer(Image R, Image G, Image B, int height, int width, int maxVal) {
    Image img;
    img.width = width;
    img.height = height;
    img.maxVal = maxVal;
    img.data = vector<vector<Pixel>>(height, vector<Pixel>(width));
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img.data[i][j].r = R.data[i][j].r;
            img.data[i][j].g = G.data[i][j].g;
            img.data[i][j].b = B.data[i][j].b;
        }
    }
    return img;

}

void make_ppm(const Image& img, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Erro ao criar o file: " << filename << endl;
        return;
    }
    file << "P3" << endl;
    file << img.width << " " << img.height << endl;
    file << img.maxVal << endl;
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            file << img.data[i][j].r << " "
            << img.data[i][j].g << " "
            << img.data[i][j].b << " ";
        }
        file << endl;
    }
    file.close();
    cout << "Saved: " << filename << endl;
}
