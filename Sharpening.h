//
// Created by Дарья Фомина on 24.03.2023.
//

#pragma once

#include "MatrixFilter.h"
#include "Filter.h"
#include "Image.h"
#include <vector>

const std::vector<std::vector<double>> SHARP_MATRIX = {{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}};

class Sharpening : public MatrixFilter {
public:
    Sharpening();

private:
};
