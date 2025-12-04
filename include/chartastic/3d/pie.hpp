#ifndef GRAPHLIB_3D_PIE_HPP
#define GRAPHLIB_3D_PIE_HPP

#include <chartastic/core/concepts.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>
#include <vector>

namespace chartastic {

class PiePlot3D : public Plot{
private:
    std::vector<double> values;
    std::vector<Color> palette;

    void renderChart() const;

public:
    /* default constructor */
    PiePlot3D(){
        title_ = "Pieplot";
        palette = {DARKGREEN, PINK, BEIGE, GRAY, LIGHTGRAY, SKYBLUE, BLACK, RED,
            GREEN, BLUE, ORANGE, YELLOW, BROWN, LIME, GOLD, DARKBLUE, DARKGRAY, VIOLET, DARKBROWN, DARKPURPLE, PURPLE};
    }

    /* constructor */
    template <chartastic::NumericIterator nit>
    PiePlot3D(nit start, nit end){
        title_ = "Pieplot";

        palette = {DARKGREEN, PINK, BEIGE, GRAY, LIGHTGRAY, SKYBLUE, BLACK, RED,
            GREEN, BLUE, ORANGE, YELLOW, BROWN, LIME, GOLD, DARKBLUE, DARKGRAY, VIOLET, DARKBROWN, DARKPURPLE, PURPLE};

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

    const std::vector<Color>& getPalette() const{
        return palette;
    }

    /* setters */
    void setValues(std::vector<double> vec){
        if (vec.empty()) {
            throw ChartasticError("Cannot have a pieplot with empty data");
        }
        values = vec;
    }

    void setPalette(std::vector<Color> vec){
        if (vec.empty()) {
            throw ChartasticError("Cannot have a pieplot with empty color palette");
        }
        palette = vec;
    }
};

}
#endif
