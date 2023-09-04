//
// Created by Дарья Фомина on 23.03.2023.
//

#include "bmp.h"
Image Bmp::Read() {
    Image empty;
    unsigned char file_header[FILE_HEADER_SIZE];
    my_file_.read(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
    if ((file_header[0] != 'B') || (file_header[1] != 'M')) {
        my_file_.close();
        throw std::runtime_error("Format of your input file is not .bmp");
    }
    unsigned char info_header[INFORMATION_HEADER_SIZE];
    my_file_.read(reinterpret_cast<char *>(info_header), INFORMATION_HEADER_SIZE);
    const size_t file_size =
        file_header[2] + (file_header[3] << BIT_8) + (file_header[4] << (2 * BIT_8)) + (file_header[5] << (3 * BIT_8));
    const size_t width =
        info_header[4] + (info_header[5] << BIT_8) + (info_header[6] << (2 * BIT_8)) + (info_header[7] << (3 * BIT_8));
    const size_t height = info_header[8] + (info_header[9] << BIT_8) + (info_header[10] << (2 * BIT_8)) +
                          (info_header[11] << (3 * BIT_8));
    Image ans(height, width);
    ans.SetFileSize(file_size);
    const int64_t padding_amount = static_cast<int64_t>((4 - ((width * 3) % 4)) % 4);
    for (ssize_t y = static_cast<ssize_t>(height) - 1; y >= 0; --y) {
        for (ssize_t x = 0; x < width; ++x) {
            unsigned char my_color[3];
            my_file_.read(reinterpret_cast<char *>(my_color), 3);
            double red = static_cast<double>(my_color[2]) / MAX_COLOR;
            double green = static_cast<double>(my_color[1]) / MAX_COLOR;
            double blue = static_cast<double>(my_color[0]) / MAX_COLOR;
            Image::Color cur_color(red, green, blue);
            ans.SetColor(x, y, cur_color);
        }
        my_file_.ignore(padding_amount);
    }
    return ans;
}

void Bmp::Print(const Image &my_image) {
    if (my_image.GetFileSize() == 0) {
        return;
    }
    const size_t width = my_image.GetWidth();
    const size_t height = my_image.GetHeight();
    unsigned char bmp_pad[3] = {0, 0, 0};
    const int64_t padding_amount = static_cast<int64_t>((4 - ((width * 3) % 4)) % 4);

    unsigned char file_header[FILE_HEADER_SIZE];
    file_header[FILE_HEADER_IND_0] = 'B';
    file_header[FILE_HEADER_IND_1] = 'M';
    const size_t file_size = my_image.GetFileSize();
    file_header[FILE_HEADER_IND_2] = file_size;
    file_header[FILE_HEADER_IND_3] = file_size >> BIT_8;
    file_header[FILE_HEADER_IND_4] = file_size >> (2 * BIT_8);
    file_header[FILE_HEADER_IND_5] = file_size >> (3 * BIT_8);
    for (size_t i = FILE_HEADER_IND_6; i < FILE_HEADER_SIZE; ++i) {
        if (i == FILE_HEADER_IND_10) {
            file_header[i] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;
        } else {
            file_header[i] = 0;
        }
    }

    unsigned char info_header[INFORMATION_HEADER_SIZE];
    info_header[INFO_HEADER_IND_0] = INFORMATION_HEADER_SIZE;
    info_header[INFO_HEADER_IND_1] = 0;
    info_header[INFO_HEADER_IND_2] = 0;
    info_header[INFO_HEADER_IND_3] = 0;
    info_header[INFO_HEADER_IND_4] = width;
    info_header[INFO_HEADER_IND_5] = width >> BIT_8;
    info_header[INFO_HEADER_IND_6] = width >> (2 * BIT_8);
    info_header[INFO_HEADER_IND_7] = width >> (3 * BIT_8);
    info_header[INFO_HEADER_IND_8] = height;
    info_header[INFO_HEADER_IND_9] = height >> BIT_8;
    info_header[INFO_HEADER_IND_10] = height >> (2 * BIT_8);
    info_header[INFO_HEADER_IND_11] = height >> (3 * BIT_8);
    info_header[INFO_HEADER_IND_12] = 1;
    info_header[INFO_HEADER_IND_13] = 0;
    info_header[INFO_HEADER_IND_14] = (3 * BIT_8);
    for (size_t i = INFO_HEADER_IND_15; i < INFORMATION_HEADER_SIZE; ++i) {
        info_header[i] = 0;
    }
    my_file_.write(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
    my_file_.write(reinterpret_cast<char *>(info_header), INFORMATION_HEADER_SIZE);
    for (ssize_t y = static_cast<ssize_t>(height) - 1; y >= 0; --y) {
        for (ssize_t x = 0; x < width; ++x) {
            unsigned char red = static_cast<unsigned char>(my_image.GetColor(x, y).r_ * MAX_COLOR);
            unsigned char green = static_cast<unsigned char>(my_image.GetColor(x, y).g_ * MAX_COLOR);
            unsigned char blue = static_cast<unsigned char>(my_image.GetColor(x, y).b_ * MAX_COLOR);
            unsigned char my_color[3] = {blue, green, red};
            my_file_.write(reinterpret_cast<char *>(my_color), 3);
        }
        my_file_.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
    }
}

Bmp::Bmp() {
}

Bmp::Bmp(const std::string &image_path, bool is_out) {
    if (is_out) {
        my_file_.open(image_path, std::ios::out | std::ios::binary);
    } else {
        my_file_.open(image_path, std::ios::in | std::ios::binary);
    }
    if (!my_file_.is_open()) {
        throw std::runtime_error("Your file could not be open");
    }
}

Bmp::~Bmp() {
    my_file_.close();
}
