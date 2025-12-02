// include/graphlib/2d/area.hpp
#ifndef GRAPHLIB_2D_AREA_HPP
#define GRAPHLIB_2D_AREA_HPP

#include <vector>
#include <string>
#include <raylib.h>
#include <chartastic/2d/plot.hpp>

namespace chartastic {

class AreaPlot : public Plot {
public:
    std::vector<std::string> x_labels;
    std::vector<double> y_values;
    Color fill_color = SKYBLUE;

    void show() const override;
};

template <typename It1, typename It2>
AreaPlot area(It1 x_begin, It1 x_end, It2 y_begin, It2 y_end) {
    AreaPlot p;
    p.x_labels.assign(x_begin, x_end);
    p.y_values.assign(y_begin, y_end);
    return p;
}

} // namespace graphlib

#endif
