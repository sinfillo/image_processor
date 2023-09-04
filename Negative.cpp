//
// Created by Дарья Фомина on 23.03.2023.
//

#include "Negative.h"

Negative::Negative() {
}

Image Negative::Apply(const Image &base_image) {
    Image ans(base_image.GetHeight(), base_image.GetWidth());
    for (ssize_t y = 0; y < ans.GetHeight(); ++y) {
        for (ssize_t x = 0; x < ans.GetWidth(); ++x) {
            auto cur_color = base_image.GetColor(x, y);
            auto new_color = Image::Color(1 - cur_color.r_, 1 - cur_color.g_, 1 - cur_color.b_);
            ans.SetColor(x, y, new_color);
        }
    }

    const int64_t padding_amount = static_cast<int64_t>((4 - ((ans.GetWidth() * 3) % 4)) % 4);
    const size_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + ans.GetWidth() * ans.GetHeight() * 3 +
                             padding_amount * ans.GetHeight();
    ans.SetFileSize(file_size);
    return ans;
}
