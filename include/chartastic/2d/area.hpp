// include/graphlib/2d/area.hpp
#ifndef GRAPHLIB_2D_AREA_HPP
#define GRAPHLIB_2D_AREA_HPP

#include <vector>
#include <string>
#include <raylib.h>
#include <chartastic/core/error.hpp>
#include <chartastic/2d/plot.hpp>

namespace chartastic {

class AreaPlot : public Plot {
private:
    std::vector<std::string> x_labels_;
    std::vector<double> y_values_;
    Color fill_color_ = SKYBLUE;

    // Helper method for rendering the chart
    void renderChart() const;

public:
    AreaPlot() {
        title_ = "Area Plot";
    }

    template <typename It1, typename It2>
    AreaPlot(It1 x_begin, It1 x_end, It2 y_begin, It2 y_end) {
        title_ = "Area Plot";
        x_labels_.assign(x_begin, x_end);
        y_values_.assign(y_begin, y_end);

        // Validate data
        if (x_labels_.empty()) {
            throw ChartasticError("Cannot create area plot with empty data");
        }

        if (x_labels_.size() != y_values_.size()) {
            throw ChartasticError("X labels size (" + std::to_string(x_labels_.size()) +
                                ") must match Y values size (" + std::to_string(y_values_.size()) + ")");
        }

        if (x_labels_.size() < 2) {
            throw ChartasticError("Area plot requires at least 2 data points, got " +
                                std::to_string(x_labels_.size()));
        }
    }

    void show() const override;
    void exportAs(const std::string& filename) const;

    // Getters
    const std::vector<std::string>& getXLabels() const { return x_labels_; }
    const std::vector<double>& getYValues() const { return y_values_; }
    Color getFillColor() const { return fill_color_; }

    // Setters
    void setXLabels(const std::vector<std::string>& labels) {
        if (labels.empty()) {
            throw ChartasticError("X labels cannot be empty");
        }
        if (labels.size() < 2) {
            throw ChartasticError("Area plot requires at least 2 data points, got " +
                                std::to_string(labels.size()));
        }
        if (!y_values_.empty() && labels.size() != y_values_.size()) {
            throw ChartasticError("X labels size (" + std::to_string(labels.size()) +
                                ") must match Y values size (" + std::to_string(y_values_.size()) + ")");
        }
        x_labels_ = labels;
    }

    void setYValues(const std::vector<double>& values) {
        if (values.empty()) {
            throw ChartasticError("Y values cannot be empty");
        }
        if (values.size() < 2) {
            throw ChartasticError("Area plot requires at least 2 data points, got " +
                                std::to_string(values.size()));
        }
        if (!x_labels_.empty() && values.size() != x_labels_.size()) {
            throw ChartasticError("Y values size (" + std::to_string(values.size()) +
                                ") must match X labels size (" + std::to_string(x_labels_.size()) + ")");
        }
        y_values_ = values;
    }

    void setFillColor(Color color) { fill_color_ = color; }
};

} // namespace graphlib

#endif
