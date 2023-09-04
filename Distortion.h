//
// Created by Дарья Фомина on 26.03.2023.
//

#pragma once

#include "Filter.h"
#include "Image.h"

#include <vector>
#include <set>
#include <cmath>
#include <queue>
static const double INF = 1e9 + 10;

class Distortion : public Filter {
public:
    Distortion();
    explicit Distortion(const size_t cnt_iters);
    Image Apply(const Image &base_image) override;

private:
    struct Info {
        size_t x_coord_;
        size_t y_coord_;
        double dist_;
        bool operator<(const Info &other) const;
        bool operator>(const Info &other) const;
    };
    size_t cnt_iters_;
    static double Dist(const Image::Color &a, const Image::Color &b);
};
