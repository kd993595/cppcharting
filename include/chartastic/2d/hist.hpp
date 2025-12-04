#ifndef GRAPHLIB_2D_HIST_HPP
#define GRAPHLIB_2D_HIST_HPP

#include <cmath>
#include <chartastic/core/concepts.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace chartastic {

class HistPlot : public Plot{
private:
    std::vector<double> values;

    int bin_count;
    Color color;

    void renderChart() const;

public:
    /* default constructor */
    HistPlot(){
        title_ = "Histogram";
        bin_count = 1;
        color = BLUE;
    }

    /* constructor */
    template <chartastic::NumericIterator nit>
    HistPlot(nit start, nit end, int count = 0){
        title_ = "Histogram";

        for (auto it = start; it != end; ++it){
            values.push_back(*it);
        }

        // Validate data
        if (values.empty()){
            throw ChartasticError("Cannot create a histogram with empty data");
        }

        if (count < 0){
            throw ChartasticError("Cannot create a histogram with a negative bin count");
        }
        /* use default bin_count since user didn't specify */
        else if (count == 0){
            bin_count = std::ceil(std::sqrt(values.size()));
        }
        else{
            bin_count = count;
        }
    }

    void show() const override;

    /* getters */
    const std::vector<double>& getValues() const{
        return values;
    }

    int getBinCount() const{
        return bin_count;
    }

    Color getColor() const{
        return color;
    }

    /* setters */
    void setValues(std::vector<double> vec){
        if (vec.empty()) {
            throw ChartasticError("Cannot have a histogram with empty data");
        }
        values = vec;
    }

    void setBinCount(int count){
        if (count < 0){
            throw ChartasticError("Cannot have a histogram with a negative bin count");
        }
        else if (count == 0){
            bin_count = std::ceil(std::sqrt(values.size()));
        }
        else{
            bin_count = count;
        }
    }

    void setColor(Color c){
        color = c;
    }
};

}
#endif
