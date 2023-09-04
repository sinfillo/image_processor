//
// Created by Дарья Фомина on 23.03.2023.
//

#pragma once

#include "Filter.h"
#include "Image.h"

class Negative : public Filter {
public:
    Negative();
    Image Apply(const Image& base_image) override;
};
