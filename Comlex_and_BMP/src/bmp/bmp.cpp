#include "bmp.h"
#include "..\math\complex.h"

/*w and h in pixels; one pixel equals 3 bytes*/

bmp::bmp(uint32_t w, uint32_t h){
    uint32_t w_line = 3 * w  + ((4 - (w * 3) % 4) % 4);
    const uint32_t ImSize = w_line * h * sizeof(RGB);
    header.Signature = 'MB';
    header.FileSize = sizeof(Header) + sizeof(InfoHeader) + ImSize;
    header.Reserved = 0;
    header.DataOffset = sizeof(Header) + sizeof(InfoHeader);

    info.Size = 40;
    info.Width = w;
    info.Height = h;
    info.Planes = 1;
    info.BitCount = 24;
    info.Compression = 0;
    info.ImageSize = ImSize;
    info.XpixelsPerM = 1000;
    info.YpixelsPerM = 1000;
    info.ColorsUsed = 0;
    info.ColorsImportant = 0;

    data.resize(ImSize);
}

void bmp::save(const std::string& fn){
    std::ofstream f(fn, std::ios::binary);
    f.write(reinterpret_cast<const char*> (&header), sizeof(header));
    f.write(reinterpret_cast<const char*> (&info), sizeof(info));
    f.write(reinterpret_cast<const char*> (data.data()), data.size());
    }

void bmp::setPixel(uint32_t x, uint32_t y, const RGB& color){
    uint32_t cellNumber = y * (info.Width * 3 + ((4 - (info.Width * 3) % 4) % 4)) + 3 * x;
    data[cellNumber + 0] = color.B;
    data[cellNumber + 1] = color.G;
    data[cellNumber + 2] = color.R;
}

void bmp::DrawComplex(double re_min, double im_min, double re_max, double im_max, int n_max){
    for (int y = 0; y < info.Height; y++)
    {
        for (int x = 0; x < info.Width; x++)
        {
            Complex z = Complex::Mapping(*this, x, y, re_min, im_min, re_max, im_max);
            int n = Complex::iterate(z, n_max);

            RGB pixelColor;
            if (n == n_max) {
                pixelColor = RGB(0, 0, 0);
            } else {
                uint8_t val = 255 * n / n_max;
                pixelColor = RGB(val, val, val);
            }

            setPixel(x, y, pixelColor);
        }
        
    }
    
}