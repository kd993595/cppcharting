#ifndef GRAPHLIB_2D_BAR_HPP
#define GRAPHLIB_2D_BAR_HPP

#include <vector>
#include <graphlib/core/concepts.hpp>

namespace graphlib {


class BarPlot {
public:
    std::vector<std::string> x_labels;  // categorical
    std::vector<double> y_values;

    BarPlot() = default;

    void show() const;
};

template <graphlib::StringIterator XIt, graphlib::NumericIterator YIt>
BarPlot bar(XIt x_begin, XIt x_end, YIt y_begin, YIt y_end) {
    BarPlot plot;

    for (auto it = x_begin; it != x_end; ++it)
        plot.x_labels.push_back(std::string(*it));

    for (auto it = y_begin; it != y_end; ++it)
        plot.y_values.push_back(static_cast<double>(*it));

    return plot;
}

}
#endif // GRAPHLIB_2D_BAR_HPP
