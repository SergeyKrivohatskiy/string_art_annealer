#pragma once
#include "bresenham.hpp"
#include <algorithm>
#include <random>

inline std::vector<point_t> generate_circle_pins(
    size_t const size_h, size_t const size_w, size_t const pins_count)
{
    double r = std::min(size_h, size_w) / 2.3;
    std::vector<point_t> pins;
    pins.reserve(pins_count);
    static double const TWO_PI = 3.1415926535897 * 2.0;
    for (size_t pinIdx = 0; pinIdx < pins_count; ++pinIdx)
    {
        double const degR = (TWO_PI * pinIdx) / pins_count;
        pins.push_back(std::make_pair(
            static_cast<int>(size_h / 2 + r * cos(degR)),
            static_cast<int>(size_w / 2 + r * sin(degR))));
    }
    return pins;
}


inline std::vector<size_t> generate_initial_path(
    size_t const path_length, size_t const pins_count,
    std::mt19937 &rng)
{
    std::uniform_int_distribution<size_t> uni(0, pins_count - 1);
    std::vector<size_t> initial_path(path_length);
    std::generate(initial_path.begin(), initial_path.end(), [&uni, &rng]() {
        return uni(rng);
    });
    return initial_path;
}

inline std::pair<size_t, size_t> random_mutation(
    size_t const path_length, size_t const pins_count,
    std::mt19937 &rng)
{
    std::uniform_int_distribution<size_t> pos(0, path_length - 1);
    std::uniform_int_distribution<size_t> pin(0, pins_count - 1);
    return std::make_pair(pos(rng), pin(rng));
}


//def fill_field(size_h, size_w, current_path, pins_to_pins_lines):
//    field = np.zeros((size_h, size_w), np.int32)
//    path_length = len(current_path)
//    for lineIdx in range(0, path_length):
//        if lineIdx == 0:
//            pin_0_idx = path_length - 1
//        else:
//            pin_0_idx = lineIdx - 1
//        line = pins_to_pins_lines[current_path[pin_0_idx]][current_path[lineIdx]]
//        for point in line:
//            field[point[0], point[1]] += 1
//    return field