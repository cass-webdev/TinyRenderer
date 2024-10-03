/*
    Pulled directly from https://github.com/ssloy/tinyrenderer
*/

#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

#pragma pack(push,1)
// ^ what does "pack" do - https://stackoverflow.com/questions/3318410/pragma-pack-effect
// pack structure members with alignment
//  - structures, when declared, will insert padding between members to ensure they're aligned to appropriate addresses in memory
// - usually a multiple of the type's size
// why it's used?
// - performance penalties or sometimes errors on some archs associated w/ accessing variables that aren't aligned properly
struct TGAHeader {
    std::uint8_t  idlength = 0;
    std::uint8_t  colormaptype = 0;
    std::uint8_t  datatypecode = 0;
    std::uint16_t colormaporigin = 0;
    std::uint16_t colormaplength = 0;
    std::uint8_t  colormapdepth = 0;
    std::uint16_t x_origin = 0;
    std::uint16_t y_origin = 0;
    std::uint16_t width = 0;
    std::uint16_t height = 0;
    std::uint8_t  bitsperpixel = 0;
    std::uint8_t  imagedescriptor = 0;
};
#pragma pack(pop)

struct TGAColor {
    std::uint8_t bgra[4] = { 0,0,0,0 };
    std::uint8_t bytespp = 4;
    std::uint8_t& operator[](const int i) { return bgra[i]; }
};

struct TGAImage {
    enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

    TGAImage() = default;
    TGAImage(const int w, const int h, const int bpp);
    bool  read_tga_file(const std::string filename);
    bool write_tga_file(const std::string filename, const bool vflip = true, const bool rle = true) const;
    void flip_horizontally();
    void flip_vertically();
    TGAColor get(const int x, const int y) const;
    void set(const int x, const int y, const TGAColor& c);
    int width()  const;
    int height() const;
private:
    bool   load_rle_data(std::ifstream& in);
    bool unload_rle_data(std::ofstream& out) const;

    int w = 0;
    int h = 0;
    std::uint8_t bpp = 0;
    std::vector<std::uint8_t> data = {};
};