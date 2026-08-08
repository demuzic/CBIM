#include "../include/core/image.h"
#include "../include/core/kernel.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<Image> img(10);
    vector<Kernel> kernels(50);
    string line;
    while(1) {
        getline(cin, line);
        stringstream ss(line);
        string command, param1, param2, param3, param4;
        ss >> command >> param1 >> param2 >> param3 >> param4;
        if (command == "help") {
            cout << "use \"magick imagem.png -compress none imagem.ppm\" to convert to ppm" << endl;
            cout << "load [image idx] [file name]" << endl;
            cout << "loadk [kernel idx] [file name]" << endl;
            cout << "makek [kernel idx] [u] [v]" << endl;
            cout << "drawk [kernel idx]" << endl;
            cout << "makebl [image idx] [image red idx] [image green idx] [image blue idx] " << endl;
            cout << "applyk [image idx original] [kernel idx] [image idx result] [layer RGB. RGB = -1, R = 0, G = 1 and B = 2]" << endl;
            cout << "saveppm [image idx] [filename.ppm]" << endl;
        }
        else if (command == "load") {
            Image _image = load_image(param2);
            if (_image.data.empty()) {
                cout << "error to load: " << param1 << endl;
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
            Kernel _k = kernels[stoi(param1)];
            for (int v = 0; v < _k.height; v++) {
                for (int u = 0; u < _k.width; u++) {
                    cout << _k.data[v][u] << " ";
                }
                cout << endl;
            }
        }
        else if (command == "applyk") {
            img[stoi(param3)] = apply_kernel(img[stoi(param1)], kernels[stoi(param2)], stoi(param4));
        }
        else if (command == "makebl") {
            img[stoi(param1)] = create_image_by_layer(img[stoi(param2)], img[stoi(param3)], img[stoi(param4)], img[stoi(param2)].height, img[stoi(param2)].width, img[stoi(param2)].maxVal);
        }
        else if (command == "saveppm") {
            make_ppm(img[stoi(param1)], param2);
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
}
