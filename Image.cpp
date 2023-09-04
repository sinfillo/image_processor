//
// Created by Дарья Фомина on 21.03.2023.
//

#include "Image.h"
Image::Color::Color() {
}

Image::Color::Color(double r, double g, double b) : r_(r), g_(g), b_(b) {
}

Image::Color Image::Color::operator+(const Image::Color& other) const {
    return Image::Color(r_ + other.r_, g_ + other.g_, b_ + other.b_);
}

Image::Color Image::Color::operator-(const Image::Color& other) const {
    return Image::Color(r_ - other.r_, g_ - other.g_, b_ - other.b_);
}

Image::Color Image::Color::operator*(const double val) const {
    return Image::Color(r_ * val, g_ * val, b_ * val);
}

Image::Color Image::Color::operator+=(const Image::Color& other) {
    r_ += other.r_;
    g_ += other.g_;
    b_ += other.b_;
    return *this;
}

Image::Color Image::Color::operator-=(const Image::Color& other) {
    r_ -= other.r_;
    g_ -= other.g_;
    b_ -= other.b_;
    return *this;
}

Image::Color Image::Color::operator*=(const double val) {
    r_ *= val;
    g_ *= val;
    b_ *= val;
    return *this;
}

bool Image::Color::operator==(const Image::Color& other) const {
    if (std::abs(other.r_ - r_) > EPS) {
        return false;
    }
    if (std::abs(other.b_ - b_) > EPS) {
        return false;
    }
    if (std::abs(other.g_ - g_) > EPS) {
        return false;
    }
    return true;
}

Image::Image() {
}

Image::Image(size_t height, size_t width)
    : height_(height),
      width_(width),
      image_colors_(std::vector<std::vector<Color>>(height, std::vector<Color>(width))) {
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

Image::Color& Image::GetColor(const ssize_t x, const ssize_t y) {
    std::pair<ssize_t, ssize_t> new_coord = NormalizeCoordinates(y, x);
    return image_colors_[new_coord.first][new_coord.second];
}

const Image::Color& Image::GetColor(const ssize_t x, const ssize_t y) const {
    std::pair<ssize_t, ssize_t> new_coord = NormalizeCoordinates(y, x);
    return image_colors_[new_coord.first][new_coord.second];
}

void Image::SetColor(const ssize_t x, const ssize_t y, const Image::Color& my_color) {
    std::pair<ssize_t, ssize_t> new_coord = NormalizeCoordinates(y, x);
    image_colors_[new_coord.first][new_coord.second] = my_color;
}

std::pair<ssize_t, ssize_t> Image::NormalizeCoordinates(const ssize_t x, const ssize_t y) const {
    std::pair<ssize_t, ssize_t> ans = {x, y};
    if (x < 0) {
        ans.first = 0;
    } else if (x >= height_) {
        ans.first = static_cast<ssize_t>(height_) - 1;
    }
    if (y < 0) {
        ans.second = 0;
    } else if (y >= width_) {
        ans.second = static_cast<ssize_t>(width_) - 1;
    }
    return ans;
}

size_t Image::GetFileSize() const {
    return file_size_;
}

void Image::SetHeight(const size_t height) {
    height_ = height;
}

void Image::SetWidth(const size_t width) {
    width_ = width;
}

void Image::SetFileSize(const size_t file_size) {
    file_size_ = file_size;
}

void Image::EraseColor(size_t x, size_t y) {
    auto it = image_colors_[y].begin();
    std::advance(it, x);
    image_colors_[y].erase(it);
}
