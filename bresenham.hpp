#pragma once
#include <vector>

typedef std::pair<int, int> point_t;
typedef std::vector<point_t> path_t;

inline path_t bresenham(point_t start, point_t end)
{
    bool const steep = abs(end.second - start.second) > abs(end.first - start.first);

    if (steep)
    {
        std::swap(start.first, start.second);
        std::swap(end.first, end.second);
    }

    if (start.first > end.first)
    {
        std::swap(start, end);
    }

    int const dx = end.first - start.first;
    int const dy = abs(end.second - start.second);
    double error = 0;
    double const derr = dy / static_cast<double>(dx);

    int y = start.second;

    int const ystep = start.second < end.second ? 1 : -1;

    path_t path;
    path.reserve(dx + 1);
    for (int x = start.first + 1; x < end.first; ++x)
    {
        path.push_back(steep ? std::make_pair(y, x) : std::make_pair(x, y));
        error += derr;
        if (error >= 0.5)
        {
            y += ystep;
            error -= 1.0;
        }
    }

    return path;
}


inline std::vector< std::vector<path_t> > generate_pins_to_pins_lines(
    std::vector<point_t> const &pinPositions)
{
    size_t const pinsCount = pinPositions.size();
    std::vector< std::vector<path_t> >pins_to_pins_paths(pinsCount);
    for (size_t i = 0; i < pinsCount; ++i)
    {
        pins_to_pins_paths[i].resize(i + 1);
        for (int j = 0; j <= i; ++j) {
            pins_to_pins_paths[i][j] = std::move(
                bresenham(pinPositions[i], pinPositions[j]));
        }
    }
    return pins_to_pins_paths;
}