//
// Created by Дарья Фомина on 23.03.2023.
//

#include "Grayscale.h"
#include <cmath>

Grayscale::Grayscale() {
}

Image Grayscale::Apply(const Image &base_image) {
    Image ans(base_image.GetHeight(), base_image.GetWidth());
    for (ssize_t y = 0; y < ans.GetHeight(); ++y) {
        for (ssize_t x = 0; x < ans.GetWidth(); ++x) {
            auto cur_color = base_image.GetColor(x, y);
            const double new_color_pix = cur_color.r_ * MUL_RED + cur_color.g_ * MUL_GREEN + cur_color.b_ * MUL_BLUE;
            auto new_color = Image::Color(new_color_pix, new_color_pix, new_color_pix);
            ans.SetColor(x, y, new_color);
        }
    }

    const int64_t padding_amount = static_cast<int64_t>((4 - ((ans.GetWidth() * 3) % 4)) % 4);
    const size_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + ans.GetWidth() * ans.GetHeight() * 3 +
                             padding_amount * ans.GetHeight();
    ans.SetFileSize(file_size);
    return ans;
}
