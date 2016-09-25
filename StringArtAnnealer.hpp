#pragma once
#include "bresenham.hpp"
#include <Annealer.hpp>

typedef size_t field_val_t;
typedef std::vector< std::vector<field_val_t> > field_t;

struct PathAndField
{
    std::vector<size_t> path;
    field_t field;
    long long energy;
};


class StringArtAnnealer : public simanneal_cpp::Annealer<PathAndField>
{
public:
    typedef simanneal_cpp::Annealer<PathAndField> super;

    StringArtAnnealer(field_t const &targetImage, size_t pinsCount, size_t pathLen);

private:
    energy_t moveState(PathAndField &state) const override;
    long long applyPath(path_t const &path, field_t &field, bool remove) const;
    path_t const &getPath(size_t pin1, size_t pin2) const;

private:
    field_t m_targetImage;
    std::vector<point_t> m_pinPositions;
    std::vector< std::vector<path_t> > m_precalculatedPaths;
    size_t m_pinsCount;
    size_t m_pathLen;
    mutable std::mt19937 m_rng;
};