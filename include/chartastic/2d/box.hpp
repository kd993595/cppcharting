#ifndef GRAPHLIB_2D_BOX_HPP
#define GRAPHLIB_2D_BOX_HPP

#include <chartastic/core/concepts.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace chartastic {

class BoxPlot : public Plot{
private:
    std::vector<double> values;
    Color color;

    void renderChart() const;

public:
    /* default constructor */
    BoxPlot(){
        title_ = "Boxplot";
        color = BLUE;
    }

    /* constructor */
    template <chartastic::NumericIterator nit>
    BoxPlot(nit start, nit end){
        title_ = "Boxplot";

        for (auto it = start; it != end; ++it){
            values.push_back(*it);
        }

        // Validate data
        if (values.empty()){
            throw ChartasticError("Cannot create a boxplot with empty data");
        }
    }

    void show() const override;

    /* getters */
    const std::vector<double>& getValues() const{
        return values;
    }

    Color getColor() const{
        return color;
    }

    /* setters */
    void setValues(std::vector<double> vec){
        if (vec.empty()) {
            throw ChartasticError("Cannot have a boxplot with empty data");
        }
        values = vec;
    }

    void setColor(Color c){
        color = c;
    }
};

}
#endif
