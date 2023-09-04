//
// Created by Дарья Фомина on 21.03.2023.
//

#pragma once

#include <iostream>
#include <vector>

static const double EPS = 1e-5;
static const size_t FILE_HEADER_SIZE = 14;
static const size_t INFORMATION_HEADER_SIZE = 40;
static const double MAX_COLOR = 255.0;

class Image {
public:
    class Color {
    public:
        double r_ = 0;
        double g_ = 0;
        double b_ = 0;
        Color();
        Color(double r, double g, double b);
        Color operator+(const Color& other) const;
        Color operator-(const Color& other) const;
        Color operator*(const double val) const;
        Color operator+=(const Color& other);
        Color operator-=(const Color& other);
        Color operator*=(const double val);
        bool operator==(const Color& other) const;
        bool operator!=(const Color& other) const = default;
    };
    Image();
    Image(size_t height, size_t width);
    size_t GetHeight() const;
    size_t GetWidth() const;
    size_t GetFileSize() const;
    Color& GetColor(const ssize_t x, const ssize_t y);
    const Color& GetColor(const ssize_t x, const ssize_t y) const;
    void SetColor(const ssize_t x, const ssize_t y, const Color& my_color);
    void SetHeight(const size_t height);
    void SetWidth(const size_t width);
    void SetFileSize(const size_t file_size);
    std::pair<ssize_t, ssize_t> NormalizeCoordinates(const ssize_t x, const ssize_t y) const;
    void EraseColor(size_t x, size_t y);

private:
    size_t height_;
    size_t width_;
    size_t file_size_;
    std::vector<std::vector<Color>> image_colors_;
};
