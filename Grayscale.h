//
// Created by Дарья Фомина on 23.03.2023.
//

#pragma once

#include "Filter.h"
#include "Image.h"
const double MUL_RED = 0.299;
const double MUL_GREEN = 0.587;
const double MUL_BLUE = 0.114;

class Grayscale : public Filter {
public:
    Grayscale();
    Image Apply(const Image& base_image) override;
};
