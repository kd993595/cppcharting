#ifndef GRAPHLIB_2D_HIST_HPP
#define GRAPHLIB_2D_HIST_HPP

#include <cmath>
#include <chartastic/core/concepts.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace chartastic {

class HistPlot : public chartastic::Plot{
public:
    std::vector<double> values;
    std::string title = "Title";

    double bin_count = 1;
    Color color = BLUE;

    void show() const override;
};

template <chartastic::NumericIterator nit>
HistPlot hist(nit start, nit end, double count = 0){
    HistPlot plot;

    for (auto it = start; it != end; ++it){
        plot.values.push_back(*it);
    }

    /* use default bin_count since user didn't specify */
    if (!count){
        plot.bin_count = std::ceil(std::sqrt(plot.values.size()));
    }
    else{
        plot.bin_count = count;
    }
    return plot;
}

}
#endif
