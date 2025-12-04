#ifndef GRAPHLIB_2D_PIE_HPP
#define GRAPHLIB_2D_PIE_HPP

#include <chartastic/core/concepts.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace chartastic {

class PiePlot : public Plot{
private:
    std::vector<double> values;

    void renderChart() const;

public:
    /* default constructor */
    PiePlot(){
        title_ = "Pieplot";
    }

    /* constructor */
    template <chartastic::NumericIterator nit>
    PiePlot(nit start, nit end){
        title_ = "Pieplot";

        for (auto it = start; it != end; ++it){
            values.push_back(*it);
        }

        // Validate data
        if (values.empty()){
            throw ChartasticError("Cannot create a pieplot with empty data");
        }
    }

    void show() const override;

    /* getters */
    const std::vector<double>& getValues() const{
        return values;
    }

    /* setters */
    void setValues(std::vector<double> vec){
        if (vec.empty()) {
            throw ChartasticError("Cannot have a pieplot with empty data");
        }
        values = vec;
    }
};

}
#endif
