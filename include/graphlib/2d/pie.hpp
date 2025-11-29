#ifndef GRAPHLIB_2D_PIE_HPP
#define GRAPHLIB_2D_PIE_HPP

#include <graphlib/core/concepts.hpp>
#include <graphlib/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace graphlib{

class PiePlot : public Plot{
public:
    std::vector<double> values;
    std::string title = "Title";

    Color color = BLUE;

    void show() const override;
};

template <graphlib::NumericIterator nit>
PiePlot pie(nit start, nit end){
    PiePlot plot;

    for (auto it = start; it != end; ++it){
        plot.values.push_back(*it);
    }
    return plot;
}

}
#endif
