#ifndef GRAPHLIB_2D_BAR_HPP
#define GRAPHLIB_2D_BAR_HPP

#include <vector>
#include <chartastic/core/concepts.hpp>
#include <chartastic/core/error.hpp>
#include <chartastic/2d/plot.hpp>
#include <raylib.h>

namespace chartastic {

enum class Orientation {
    Vertical,
    Horizontal
};

class BarPlot : public Plot {
private:
    std::vector<std::string> x_labels_;
    std::vector<double> y_values_;
    std::vector<Color> colors_;
    Orientation orientation_ = Orientation::Vertical;

    // Helper method for rendering the chart
    void renderChart() const;

public:
    BarPlot() {
        title_ = "Bar Plot";
    }

    template <chartastic::StringIterator XIt, chartastic::NumericIterator YIt>
    BarPlot(XIt x_begin, XIt x_end, YIt y_begin, YIt y_end) {
        title_ = "Bar Plot";

        for (auto it = x_begin; it != x_end; ++it)
            x_labels_.push_back(std::string(*it));

        for (auto it = y_begin; it != y_end; ++it)
            y_values_.push_back(static_cast<double>(*it));

        // Validate data
        if (x_labels_.empty()) {
            throw ChartasticError("Cannot create bar plot with empty data");
        }

        if (x_labels_.size() != y_values_.size()) {
            throw ChartasticError("X labels size (" + std::to_string(x_labels_.size()) +
                                ") must match Y values size (" + std::to_string(y_values_.size()) + ")");
        }

        colors_.resize(y_values_.size(), BLUE);
    }

    void show() const override;
    void exportAs(const std::string& filename) const;

    // Getters
    const std::vector<std::string>& getXLabels() const { return x_labels_; }
    const std::vector<double>& getYValues() const { return y_values_; }
    const std::vector<Color>& getColors() const { return colors_; }
    Orientation getOrientation() const { return orientation_; }

    // Setters
    void setXLabels(const std::vector<std::string>& labels) {
        if (labels.empty()) {
            throw ChartasticError("X labels cannot be empty");
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
        if (!x_labels_.empty() && values.size() != x_labels_.size()) {
            throw ChartasticError("Y values size (" + std::to_string(values.size()) +
                                ") must match X labels size (" + std::to_string(x_labels_.size()) + ")");
        }
        y_values_ = values;
    }

    void setColors(const std::vector<Color>& colors) {
        if (colors.empty()) {
            throw ChartasticError("Colors vector cannot be empty");
        }
        colors_ = colors;
    }

    void setOrientation(Orientation orientation) { orientation_ = orientation; }
};

}
#endif // GRAPHLIB_2D_BAR_HPP
