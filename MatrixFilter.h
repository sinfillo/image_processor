//
// Created by Дарья Фомина on 24.03.2023.
//

#pragma once

#include "Filter.h"
#include "Image.h"
#include <vector>

const double LEFT_BORDER = 0.0;
const double RIGHT_BORDER = 1.0;

class MatrixFilter : public Filter {
public:
    MatrixFilter();
    MatrixFilter(ssize_t dx, ssize_t dy, const std::vector<std::vector<double>>& matrix);
    Image Apply(const Image& base_image) override;

protected:
    Image::Color Clamp(const Image::Color& need_clamp);
    ssize_t dx_;
    ssize_t dy_;
    std::vector<std::vector<double>> matrix_;
};
