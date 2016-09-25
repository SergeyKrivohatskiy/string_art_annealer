#include "StringArtAnnealer.hpp"
#include "helper_functions.hpp"
#include <algorithm>


namespace
{
    long long computeMetric(field_val_t v1, field_val_t v2)
    {
        return (v1 - v2) * (v1 - v2);
    }

    long long computeMetric(point_t const &p,
        field_t const &field, field_t const &targetImage)
    {
        return computeMetric(field[p.first][p.second], targetImage[p.first][p.second]);
    }

    long long energy(field_t const &targetImage)
    {
        long long sum = 0;
        for (field_t::value_type const &row:targetImage)
        { 
            for (field_val_t const &v : row)
            {
                sum += computeMetric(0, v);
            }
        }
        return sum;
    }
}


StringArtAnnealer::StringArtAnnealer(
    field_t const &targetImage, size_t pinsCount, size_t pathLen):
    super({ std::vector<size_t>(pathLen, 0), 
            field_t(targetImage.size(), field_t::value_type(targetImage[0].size(), 0)),
            energy(targetImage) },
          static_cast<energy_t>(energy(targetImage))),
    m_targetImage(targetImage),
    m_pinPositions(
        generate_circle_pins(targetImage.size(), targetImage[0].size(), pinsCount)),
    m_precalculatedPaths(generate_pins_to_pins_lines(m_pinPositions)),
    m_pinsCount(pinsCount),
    m_pathLen(pathLen)
{
}

StringArtAnnealer::energy_t StringArtAnnealer::moveState(PathAndField &state) const
{
    std::pair<size_t, size_t> const mutation = random_mutation(
        m_pathLen, m_pinsCount, m_rng);
    size_t const prevIdx = mutation.first == 0 ? m_pathLen - 1 : mutation.first - 1;
    size_t const nextIdx = mutation.first == m_pathLen - 1 ? 0 : mutation.first + 1;
    size_t const pinWas = state.path[mutation.first];
    state.energy += applyPath(getPath(state.path[prevIdx], pinWas), state.field, true);
    state.energy += applyPath(getPath(state.path[nextIdx], pinWas), state.field, true);
    state.path[mutation.first] = mutation.second;
    state.energy += applyPath(getPath(state.path[prevIdx], mutation.second), state.field, false);
    state.energy += applyPath(getPath(state.path[nextIdx], mutation.second), state.field, false);
    return static_cast<energy_t>(state.energy);
}

long long StringArtAnnealer::applyPath(path_t const & line, field_t &field, bool remove) const
{
    long long energyChange = 0;
    for (point_t const &p : line)
    {
        energyChange -= computeMetric(p, field, m_targetImage);
        field[p.first][p.second] += remove ? -1 : 1;
        energyChange += computeMetric(p, field, m_targetImage);
    }
    return energyChange;
}

path_t const & StringArtAnnealer::getPath(size_t pin1, size_t pin2) const
{
    return m_precalculatedPaths[std::max(pin1, pin2)][std::min(pin1, pin2)];
}
