//
// Created by Дарья Фомина on 23.03.2023.
//

#pragma once

#include "Filter.h"
#include "Image.h"

class Crop : public Filter {
public:
    Crop();
    Crop(size_t new_height, size_t new_width);
    Image Apply(const Image& base_image) override;

private:
    size_t new_height_;
    size_t new_width_;
};
