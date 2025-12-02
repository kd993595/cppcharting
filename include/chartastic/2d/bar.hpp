#ifndef GRAPHLIB_2D_BAR_HPP
#define GRAPHLIB_2D_BAR_HPP

#include <vector>
#include <chartastic/core/concepts.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>

namespace chartastic {

enum class Orientation {
    Vertical,
    Horizontal
};

class BarPlot : public Plot {
public:
    std::vector<std::string> x_labels;  // categorical
    std::vector<double> y_values;
    std::string title = "Bar Plot";
    std::vector<Color> colors;
    Orientation orientation = Orientation::Vertical;

    BarPlot() = default;

    void show() const override;
};

template <chartastic::StringIterator XIt, chartastic::NumericIterator YIt>
BarPlot bar(XIt x_begin, XIt x_end, YIt y_begin, YIt y_end) {
    BarPlot plot;

    for (auto it = x_begin; it != x_end; ++it)
        plot.x_labels.push_back(std::string(*it));

    for (auto it = y_begin; it != y_end; ++it)
        plot.y_values.push_back(static_cast<double>(*it));

    plot.colors.resize(plot.y_values.size(), BLUE);

    return plot;
}

}
#endif // GRAPHLIB_2D_BAR_HPP
