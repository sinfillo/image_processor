//
// Created by Дарья Фомина on 23.03.2023.
//

#pragma once

#include "Image.h"

class Filter {
public:
    Filter();
    virtual Image Apply(const Image& base_image) = 0;
};
