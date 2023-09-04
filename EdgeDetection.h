//
// Created by Дарья Фомина on 24.03.2023.
//

#pragma once

#include "MatrixFilter.h"
#include "Filter.h"
#include "Image.h"
#include "Grayscale.h"
#include <vector>

const std::vector<std::vector<double>> EDGE_MATRIX = {{0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}};

class EdgeDetection : public MatrixFilter {
public:
    EdgeDetection();
    explicit EdgeDetection(double threshold);
    Image Apply(const Image& base_image) override;

private:
    double threshold_;
    Grayscale grayscale_filter_;
    MatrixFilter matrix_filter_;
};
