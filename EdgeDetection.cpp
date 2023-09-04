//
// Created by Дарья Фомина on 24.03.2023.
//

#include "EdgeDetection.h"

EdgeDetection::EdgeDetection() {
}

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold), matrix_filter_(-1, -1, EDGE_MATRIX) {
}

Image EdgeDetection::Apply(const Image &base_image) {
    Image gray_ans = grayscale_filter_.Apply(base_image);
    Image ans = matrix_filter_.Apply(gray_ans);
    Image::Color left = Image::Color(LEFT_BORDER, LEFT_BORDER, LEFT_BORDER);
    Image::Color right = Image::Color(RIGHT_BORDER, RIGHT_BORDER, RIGHT_BORDER);
    for (ssize_t y = 0; y < ans.GetHeight(); ++y) {
        for (ssize_t x = 0; x < ans.GetWidth(); ++x) {
            if (ans.GetColor(x, y).r_ <= threshold_) {
                ans.SetColor(x, y, left);
            } else {
                ans.SetColor(x, y, right);
            }
        }
    }

    return ans;
}
