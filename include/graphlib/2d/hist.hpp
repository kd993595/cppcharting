#ifndef GRAPHLIB_2D_HIST_HPP
#define GRAPHLIB_2D_HIST_HPP

#include <graphlib/core/concepts.hpp>
#include <graphlib/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace graphlib{

class HistPlot : public graphlib::Plot{
public:
    std::vector<double> values;
    std::string title = "Title";

    double bin_width = 1;
    Color color = BLUE;

    void show() const override;
};

template <graphlib::NumericIterator nit>
HistPlot hist(nit start, nit end, double width = 1.0){
    HistPlot plot;
    plot.bin_width = width;

    for (auto it = start; it != end; ++it){
        plot.values.push_back(*it);
    }
    return plot;
}

}
#endif
