//
// Created by Дарья Фомина on 25.03.2023.
//

#pragma once

#include "MatrixFilter.h"
#include "Filter.h"
#include "Image.h"
#include <cmath>
#include <vector>
#include <iostream>

static const double MAGIC_NUMBER_TWO = 2.0;
static const int MAGIC_NUMBER_SIX = 6;

class GaussianBlur : public MatrixFilter {
public:
    GaussianBlur();
    explicit GaussianBlur(const double sigma);
    Image Apply(const Image& base_image) override;

private:
    std::vector<double> using_coeffs_;
    ssize_t dist_;
};
