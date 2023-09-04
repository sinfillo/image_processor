//
// Created by Дарья Фомина on 23.03.2023.
//

#pragma once

#include "Image.h"
#include <fstream>
#include <iostream>

static const int64_t BIT_8 = 8;

static const size_t FILE_HEADER_IND_0 = 0;
static const size_t FILE_HEADER_IND_1 = 1;
static const size_t FILE_HEADER_IND_2 = 2;
static const size_t FILE_HEADER_IND_3 = 3;
static const size_t FILE_HEADER_IND_4 = 4;
static const size_t FILE_HEADER_IND_5 = 5;
static const size_t FILE_HEADER_IND_6 = 6;
static const size_t FILE_HEADER_IND_10 = 10;

static const size_t INFO_HEADER_IND_0 = 0;
static const size_t INFO_HEADER_IND_1 = 1;
static const size_t INFO_HEADER_IND_2 = 2;
static const size_t INFO_HEADER_IND_3 = 3;
static const size_t INFO_HEADER_IND_4 = 4;
static const size_t INFO_HEADER_IND_5 = 5;
static const size_t INFO_HEADER_IND_6 = 6;
static const size_t INFO_HEADER_IND_7 = 7;
static const size_t INFO_HEADER_IND_8 = 8;
static const size_t INFO_HEADER_IND_9 = 9;
static const size_t INFO_HEADER_IND_10 = 10;
static const size_t INFO_HEADER_IND_11 = 11;
static const size_t INFO_HEADER_IND_12 = 12;
static const size_t INFO_HEADER_IND_13 = 13;
static const size_t INFO_HEADER_IND_14 = 14;
static const size_t INFO_HEADER_IND_15 = 15;

class Bmp {
public:
    Bmp();
    explicit Bmp(const std::string& image_path, bool is_out);
    Image Read();
    void Print(const Image& my_image);
    ~Bmp();

private:
    std::fstream my_file_;
};
