//
// Created by Дарья Фомина on 25.03.2023.
//

#include "GaussianBlur.h"

GaussianBlur::GaussianBlur() {
}

GaussianBlur::GaussianBlur(const double sigma) {
    dist_ = std::ceil(MAGIC_NUMBER_SIX * sigma);
    dist_ |= 1;
    using_coeffs_.resize(dist_);
    for (ssize_t x = 0; x <= dist_ / 2; ++x) {
        double st = -(static_cast<double>(x * x)) / (MAGIC_NUMBER_TWO * sigma * sigma);
        double val = 1.0 / (std::sqrt(MAGIC_NUMBER_TWO * M_PI * sigma * sigma)) * std::exp(st);
        using_coeffs_[dist_ / 2 - x] = val;
        using_coeffs_[dist_ / 2 + x] = val;
    }
}

Image GaussianBlur::Apply(const Image &base_image) {

    Image ans(base_image.GetHeight(), base_image.GetWidth());
    for (ssize_t y = 0; y < base_image.GetHeight(); ++y) {
        for (ssize_t x = 0; x < base_image.GetWidth(); ++x) {
            ans.SetColor(x, y, base_image.GetColor(x, y));
        }
    }
    Image vertical(ans.GetHeight(), ans.GetWidth());
    for (ssize_t x = 0; x < ans.GetWidth(); ++x) {
        for (ssize_t y = 0; y < ans.GetHeight(); ++y) {
            Image::Color &cur_color = vertical.GetColor(x, y) = {};
            for (ssize_t dy = -dist_ / 2; dy <= dist_ / 2; ++dy) {
                cur_color += ans.GetColor(x, y + dy) * using_coeffs_[dist_ / 2 + dy];
            }
            // vertical.SetColor(x, y, cur_color);
        }
    }
    for (ssize_t y = 0; y < ans.GetHeight(); ++y) {
        for (ssize_t x = 0; x < ans.GetWidth(); ++x) {
            Image::Color &cur_color = ans.GetColor(x, y) = {};
            for (ssize_t dx = -dist_ / 2; dx <= dist_ / 2; ++dx) {
                cur_color += vertical.GetColor(x + dx, y) * using_coeffs_[dist_ / 2 + dx];
            }
            // ans.SetColor(x, y, cur_color);
        }
    }

    const int64_t padding_amount = static_cast<int64_t>((4 - ((ans.GetWidth() * 3) % 4)) % 4);
    const size_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + ans.GetWidth() * ans.GetHeight() * 3 +
                             padding_amount * ans.GetHeight();
    ans.SetFileSize(file_size);
    return ans;
}
