//
// Created by Дарья Фомина on 26.03.2023.
//

#include "Distortion.h"

Distortion::Distortion() {
}

Image Distortion::Apply(const Image& base_image) {
    cnt_iters_ = std::min(cnt_iters_, base_image.GetWidth());
    Image ans = base_image;
    // clock_t dptime = 0;
    // clock_t pathtime = 0;
    while (cnt_iters_-- > 0) {
        std::cerr << cnt_iters_ << " iterations remain" << std::endl;
        std::vector<std::vector<double>> all_dist(ans.GetHeight(), std::vector<double>(ans.GetWidth(), INF));
        // std::vector<std::vector<char>> prev(ans.GetHeight(), std::vector<char>(ans.GetWidth(), '!'));
        // std::set<Info> que;
        //        std::priority_queue<Info, std::vector<Info>, std::greater<>> que;
        // auto start_time = clock();
        for (size_t x = 0; x < ans.GetWidth(); ++x) {
            //            que.insert(Info{.x_coord_ = x, .y_coord_ = ans.GetHeight() - 1, .dist_ = 0});
            // que.emplace(Info{.x_coord_ = x, .y_coord_ = ans.GetHeight() - 1, .dist_ = 0});
            all_dist[ans.GetHeight() - 1][x] = 0;
            // prev[ans.GetHeight() - 1][x] = '.';
        }
        /*while (!que.empty()) {
//            auto cur = que.begin();
            auto cur = *que.begin();
            if (cur.y_coord_ == 0) {
                break;
            }
            que.erase(que.begin());
//            que.pop();
            for (ssize_t dx = -1; dx <= 1; ++dx) {
                ssize_t want_x = dx + cur.x_coord_;
                ssize_t want_y = cur.y_coord_ - 1;
                if (want_x < 0 || want_x >= ans.GetWidth() || want_y < 0 || want_y >= ans.GetHeight()) {
                    continue;
                }
                double weight = Dist(ans.GetColor(want_x, want_y), ans.GetColor(cur.x_coord_, cur.y_coord_));
                if (all_dist[want_y][want_x] > all_dist[cur.y_coord_][cur.x_coord_] + weight) {
                    que.erase(Info{.x_coord_ = static_cast<size_t>(want_x), .y_coord_ = static_cast<size_t>(want_y),
.dist_ = all_dist[want_y][want_x]}); all_dist[want_y][want_x] = all_dist[cur.y_coord_][cur.x_coord_] + weight;
                    que.emplace(Info{.x_coord_ = static_cast<size_t>(want_x), .y_coord_ = static_cast<size_t>(want_y),
.dist_ = all_dist[want_y][want_x]});
//                    que.insert(Info{.x_coord_ = static_cast<size_t>(want_x), .y_coord_ = static_cast<size_t>(want_y),
.dist_ = all_dist[want_y][want_x]}); if (dx == -1) { prev[want_y][want_x] = '0'; } else if (dx == 0) {
                        prev[want_y][want_x] = '1';
                    } else {
                        prev[want_y][want_x] = '2';
                    }
                }
            }
        }*/
        if (ans.GetHeight() > 1) {
            for (ssize_t y = static_cast<ssize_t>(ans.GetHeight()) - 1; y >= 1; --y) {
                for (ssize_t x = 0; x < static_cast<ssize_t>(ans.GetWidth()); ++x) {
                    for (ssize_t dx = -1; dx <= 1; ++dx) {
                        ssize_t want_x = dx + x;
                        ssize_t want_y = y - 1;
                        if (want_x < 0 || want_x >= ans.GetWidth() || want_y < 0 || want_y >= ans.GetHeight()) {
                            continue;
                        }
                        double weight = Dist(ans.GetColor(want_x, want_y), ans.GetColor(x, y));
                        if (all_dist[want_y][want_x] > all_dist[y][x] + weight) {
                            all_dist[want_y][want_x] = all_dist[y][x] + weight;
                            /*if (dx == -1) {
                                prev[want_y][want_x] = '0';
                            } else if (dx == 0) {
                                prev[want_y][want_x] = '1';
                            } else {
                                prev[want_y][want_x] = '2';
                            }*/
                        }
                    }
                }
            }
        }
        // dptime += clock() - start_time;
        // start_time = clock();
        ssize_t x_min = -1;
        double dist_min = INF;
        for (ssize_t x = 0; x < ans.GetWidth(); ++x) {
            if (x_min == -1 || dist_min > all_dist[0][x]) {
                x_min = x;
                dist_min = all_dist[0][x_min];
            }
        }
        ssize_t cur_y = 0;
        std::vector<std::pair<size_t, size_t>> need_erase;
        while (cur_y != ans.GetHeight()) {
            // std::cerr << x_min << " " << cur_y << std::endl;
            // ans.EraseColor(x_min, cur_y);
            need_erase.push_back({static_cast<size_t>(x_min), static_cast<size_t>(cur_y)});
            ssize_t want_y = cur_y + 1;
            if (want_y == ans.GetHeight()) {
                break;
            }
            for (ssize_t dx = -1; dx <= 1; ++dx) {
                ssize_t want_x = x_min + dx;
                // std::cout << want_x << " ";
                if (want_x >= 0 && want_x < ans.GetWidth() &&
                    all_dist[want_y][want_x] + Dist(ans.GetColor(x_min, cur_y), ans.GetColor(want_x, want_y)) ==
                        all_dist[cur_y][x_min]) {
                    x_min = want_x;
                    cur_y = static_cast<ssize_t>(want_y);
                    break;
                }
            }
            // std::cout << std::endl;
        }
        for (const auto& elem : need_erase) {
            ans.EraseColor(elem.first, elem.second);
        }
        ans.SetWidth(ans.GetWidth() - 1);
        // pathtime += clock() - start_time;
    }
    const int64_t padding_amount = static_cast<int64_t>((4 - ((ans.GetWidth() * 3) % 4)) % 4);
    const size_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + ans.GetWidth() * ans.GetHeight() * 3 +
                             padding_amount * ans.GetHeight();
    ans.SetFileSize(file_size);
    /*std::cerr << "Time spent on calculating dp:  " << (double)dptime / CLOCKS_PER_SEC << std::endl
              << "Time spent on erasing path:  " << (double)pathtime / CLOCKS_PER_SEC << std::endl;*/
    return ans;
}

double Distortion::Dist(const Image::Color& a, const Image::Color& b) {
    double dist_r = a.r_ - b.r_;
    double dist_g = a.g_ - b.g_;
    double dist_b = a.b_ - b.b_;
    //    return std::abs(dist_r) + std::abs(dist_g) + std::abs(dist_b);
    return std::sqrt(dist_r * dist_r + dist_g * dist_g + dist_b * dist_b);
}

Distortion::Distortion(const size_t cnt_iters) : cnt_iters_(cnt_iters) {
}

bool Distortion::Info::operator<(const Info& other) const {
    if (other.dist_ == dist_) {
        if (other.x_coord_ == x_coord_) {
            return y_coord_ < other.y_coord_;
        }
        return x_coord_ < other.x_coord_;
    }
    return dist_ < other.dist_;
}
bool Distortion::Info::operator>(const Distortion::Info& other) const {
    return other < *this;
}
