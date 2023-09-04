//
// Created by Дарья Фомина on 23.03.2023.
//

#include "Crop.h"

Crop::Crop(size_t new_height, size_t new_width) : new_height_(new_height), new_width_(new_width) {
}

Crop::Crop() {
}

Image Crop::Apply(const Image &base_image) {
    size_t cur_height = std::min(base_image.GetHeight(), new_height_);
    size_t cur_width = std::min(base_image.GetWidth(), new_width_);
    Image ans(cur_height, cur_width);
    for (ssize_t y = 0; y < cur_height; ++y) {
        for (ssize_t x = 0; x < cur_width; ++x) {
            ans.SetColor(x, y, base_image.GetColor(x, y));
        }
    }
    const int64_t padding_amount = static_cast<int64_t>((4 - ((cur_width * 3) % 4)) % 4);
    const size_t file_size =
        FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + cur_width * cur_height * 3 + padding_amount * cur_height;
    ans.SetFileSize(file_size);
    return ans;
}
