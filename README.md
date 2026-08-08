# PPM Image Processor with Convolution

Image processor in C++ that applies convolutional filters (kernels) to files in PPM P3 (ASCII) format. Developed with a focus on modularization, interface via command line and pixel-by-pixel processing without external dependencies.

## Features
- Loading and saving PPM P3 images;
- Manual creation or loading of kernels;
- Application of convolution with edge treatment (clamping);
- Viewing kernel matrices in the terminal;
- Support multiple images and kernels in memory simultaneously.

## Compilation and Execution
```Shell
bash
make # Compile the project
./processor # Start the interactive interface. Try "help" to begin
```
## Examples

### Original
<img width="640" height="360" alt="jupiter" src="https://github.com/user-attachments/assets/a8f05b97-9421-4f91-a00f-8a4574573262" />

### Emboss filter
<img width="640" height="360" alt="jupiter_emboss" src="https://github.com/user-attachments/assets/2aceeeca-585a-475d-aaaa-1a41154bd713" />

### Gauss blur filter
<img width="640" height="360" alt="jupiter_gauss_blur" src="https://github.com/user-attachments/assets/3274760e-d041-486b-8abe-dbfc073fad7f" />

### Sharpen filter
<img width="640" height="360" alt="jupiter_sharpen" src="https://github.com/user-attachments/assets/66cc5176-e684-42cf-90e2-78da91aaaf2d" />

### Sobel filter
<img width="640" height="360" alt="jupiter_sobel" src="https://github.com/user-attachments/assets/584e1659-6372-4cc1-937e-13a059116a49" />

### blue layer chromatic aberration
<img width="640" height="360" alt="aberration" src="https://github.com/user-attachments/assets/9eb03a41-94f8-4dd1-9561-6776406286a8" />


