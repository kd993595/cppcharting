#ifndef GRAPHLIB_2D_BOX_HPP
#define GRAPHLIB_2D_BOX_HPP

#include <chartastic/core/concepts.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace chartastic {

class BoxPlot : public Plot{
public:
    std::vector<double> values;
    std::string title = "Title";

    Color color = BLUE;

    void show() const override;
};

template <chartastic::NumericIterator nit>
BoxPlot box(nit start, nit end){
    BoxPlot plot;

    for (auto it = start; it != end; ++it){
        plot.values.push_back(*it);
    }
    return plot;
}

}
#endif
