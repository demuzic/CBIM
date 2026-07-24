#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;



struct pixel {
    int r, g, b;
};

struct image {
    int maxVal;
    int width;
    int height;
    vector<vector<pixel>> data;
};

struct kernel {
    int width;
    int height;
    vector<vector<float>> data;
};

image load_image(string image_name) {

    ifstream archive(image_name);

    if(!archive.is_open()) return {};

    string type;
    int width, height, maxVal;

    archive >> type;
    archive >> width;
    archive >> height;
    archive >> maxVal;


    image img;
    img.width = width;
    img.height = height;
    img.maxVal = maxVal;
    img.data = vector<vector<pixel>>(height, vector<pixel>(width));

    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            archive >> img.data[i][j].r;
            archive >> img.data[i][j].g;
            archive >> img.data[i][j].b;

        }
    }

    return img;

}

kernel load_kernel(string kernel_name) {
    ifstream archive(kernel_name);
    if(!archive.is_open()) return {};

    int u, v;

    archive >> v;
    archive >> u;

    kernel k;
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

kernel make_kernel(int width, int height) {
    kernel k;
    k.width = width;
    k.height = height;

    k.data.resize(height);
    for (int i = 0; i < height; i++) {
        k.data[i].resize(width);
    }

    for (int v = 0; v < height; v++) {
        for (int u = 0; u < width; u++) {
            cout << u + 1<< "x" << v + 1<< ": " << endl;
            cin >> k.data[v][u];
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return k;
}

image apply_kernel(const image& img, const kernel& k) {
    image new_img;
    new_img.width = img.width;
    new_img.height = img.height;
    new_img.maxVal = img.maxVal;
    new_img.data.resize(img.height, vector<pixel>(img.width, {0,0,0}));

    int h_offset = k.width / 2;
    int v_offset = k.height / 2;

    for (int i = 0; i < new_img.height; i++) {
        for (int j = 0; j < new_img.width; j++) {

            float somaR = 0, somaG = 0, somaB = 0;

            for(int v = 0; v < k.height; v++) {
                for(int u = 0; u < k.width; u++) {

                    int iy = i + v - v_offset;
                    int ix = j + u - h_offset;

                    //CLAMPING (Prende nas bordas)
                    if (iy < 0) iy = 0;
                    else if (iy >= img.height) iy = img.height - 1;

                    if (ix < 0) ix = 0;
                    else if (ix >= img.width) ix = img.width - 1;

                    somaR += k.data[v][u] * img.data[iy][ix].r;
                    somaG += k.data[v][u] * img.data[iy][ix].g;
                    somaB += k.data[v][u] * img.data[iy][ix].b;
                }
            }

            new_img.data[i][j].r = max(0, min(255, (int)somaR));
            new_img.data[i][j].g = max(0, min(255, (int)somaG));
            new_img.data[i][j].b = max(0, min(255, (int)somaB));
        }
    }
    return new_img;
}

void make_ppm (const image& img, const string& filename) {
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
    cout << "Imagem salva em: " << filename << endl;


}

int main() {
    vector<image> img(10);
    vector<kernel> kernels(50);

    string line;
    while(1) {
        //carregar comando
        getline(cin, line);
        stringstream ss(line);
        string command, param1, param2, param3, param4;
        ss >> command;
        ss >> param1;
        ss >> param2;
        ss >> param3;
        ss >> param4;

        //comandos
        if (command == "help") {
            cout <<"use \"magick imagem.png -compress none imagem.ppm\" to convert to ppm" << endl;
            cout << "load [image idx] [file name]" << endl;
            cout << "makek [kernel idx] [u] [v]" << endl;
            cout << "drawk [kernel idx]" << endl;
            cout << "applyk [image idx original] [kernel idx] [image idx result]" << endl;
            cout << "saveppm [image idx] [filename.ppm]" << endl;
        }
        else if (command == "load") {
            image _image = load_image(param2);
            if (_image.data.empty()) {
                cout << "error to load: ";
                cout << param1 << endl;
                continue;
            }
            img[stoi(param1)] = _image;
            cout << "loaded " << param2 << " at " << param1 << " position" << endl;

        }

        else if (command == "makek") {
            kernels[stoi(param1)] = make_kernel(stoi(param2), stoi(param3));
        }

        else if (command == "loadk") {
            kernels[stoi(param1)] = load_kernel(param2);
        }

        else if(command == "drawk") {

            kernel _k = kernels[stoi(param1)];

            for (int v = 0; v < _k.height; v++) {
                for (int u = 0; u < _k.width; u++) {
                cout << _k.data[v][u] << " ";
                }
                cout << endl;
            }

        }

        else if (command == "applyk") {

            img[stoi(param3)] = apply_kernel(img[stoi(param1)], kernels[stoi(param2)]);
        }

        else if (command == "saveppm") {
            make_ppm(img[stoi(param1)], param2);
        }

        else {
             cout << "Unknown command" << endl;
        }
    }
}
