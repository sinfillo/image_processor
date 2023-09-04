//
// Created by Дарья Фомина on 24.03.2023.
//

#include "MatrixFilter.h"

MatrixFilter::MatrixFilter() {
}

MatrixFilter::MatrixFilter(ssize_t dx, ssize_t dy, const std::vector<std::vector<double>> &matrix)
    : dx_(dx), dy_(dy), matrix_(matrix) {
}

Image::Color MatrixFilter::Clamp(const Image::Color &need_clamp) {
    Image::Color ans;
    ans.r_ = std::min(RIGHT_BORDER, std::max(LEFT_BORDER, need_clamp.r_));
    ans.g_ = std::min(RIGHT_BORDER, std::max(LEFT_BORDER, need_clamp.g_));
    ans.b_ = std::min(RIGHT_BORDER, std::max(LEFT_BORDER, need_clamp.b_));
    return ans;
}

Image MatrixFilter::Apply(const Image &base_image) {
    Image ans(base_image.GetHeight(), base_image.GetWidth());
    for (ssize_t y = 0; y < ans.GetHeight(); ++y) {
        for (ssize_t x = 0; x < ans.GetWidth(); ++x) {
            Image::Color set_color(LEFT_BORDER, LEFT_BORDER, LEFT_BORDER);
            for (ssize_t i = 0; i < matrix_.size(); ++i) {
                for (ssize_t j = 0; j < matrix_[0].size(); ++j) {
                    set_color += base_image.GetColor(x + dx_ + j, y + dy_ + i) * matrix_[i][j];
                }
            }
            ans.SetColor(x, y, Clamp(set_color));
        }
    }
    const int64_t padding_amount = static_cast<int64_t>((4 - ((ans.GetWidth() * 3) % 4)) % 4);
    const size_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + ans.GetWidth() * ans.GetHeight() * 3 +
                             padding_amount * ans.GetHeight();
    ans.SetFileSize(file_size);
    return ans;
}
