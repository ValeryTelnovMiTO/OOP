#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include<fstream>
#include <cmath>

class Complex;

#pragma pack(push,1)

struct Header
{
    short Signature;
    unsigned int FileSize;
    unsigned int Reserved;
    unsigned int DataOffset;
};

struct InfoHeader
{
    unsigned int Size;
    unsigned int Width;
    unsigned int Height;
    short Planes;
    short BitCount;
    unsigned int Compression;
    unsigned int ImageSize;
    unsigned int XpixelsPerM;
    unsigned int YpixelsPerM;
    unsigned int ColorsUsed;
    unsigned int ColorsImportant;
};

#pragma pack(pop)

struct RGB
{
    uint8_t B = 0;
    uint8_t G = 0;
    uint8_t R = 0;
    RGB() = default;
    RGB(uint8_t R, uint8_t G ,uint8_t B) : R(R), G(G), B(B){}
};

static_assert(sizeof(Header) == 14);// выравнивание до 16 байт просто так без #pragma pack(push,1)
static_assert(sizeof(InfoHeader) == 40);

class bmp
{
private:
    Header header;
    InfoHeader info;
    std::vector<uint8_t> data;
public:
    uint32_t GetWidth() const { return info.Width; }
    uint32_t GetHeight() const { return info.Height; }
    bmp(uint32_t w, uint32_t h);
    void setPixel(uint32_t x, uint32_t y, const RGB& color);
    void save(const std::string& filename);
    void DrawComplex(double re_min, double im_min, double re_max, double im_max, int n_max);
};

