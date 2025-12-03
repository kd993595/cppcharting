#ifndef CHARTASTIC_3D_BAR_HPP
#define CHARTASTIC_3D_BAR_HPP

#include <vector>
#include <string>
#include <chartastic/core/concepts.hpp>
#include <chartastic/core/error.hpp>
#include <raylib.h>

namespace chartastic {

class BarPlot3D {
private:
    std::vector<std::string> x_labels_;
    std::vector<double> y_values_;
    std::string title_ = "3D Bar Plot";
    std::vector<Color> colors_;
    int width_ = 1200;
    int height_ = 800;

    // Camera settings
    float camera_distance_ = 15.0f;
    float camera_angle_x_ = 45.0f;
    float camera_angle_y_ = 45.0f;

public:
    BarPlot3D() = default;

    template <chartastic::StringIterator XIt, chartastic::NumericIterator YIt>
    BarPlot3D(XIt x_begin, XIt x_end, YIt y_begin, YIt y_end) {
        for (auto it = x_begin; it != x_end; ++it)
            x_labels_.push_back(std::string(*it));

        for (auto it = y_begin; it != y_end; ++it)
            y_values_.push_back(static_cast<double>(*it));

        // Validate data
        if (x_labels_.empty()) {
            throw ChartasticError("Cannot create 3D bar plot with empty data");
        }

        if (x_labels_.size() != y_values_.size()) {
            throw ChartasticError("X labels size (" + std::to_string(x_labels_.size()) +
                                ") must match Y values size (" + std::to_string(y_values_.size()) + ")");
        }

        colors_.resize(y_values_.size(), BLUE);
    }

    void show() const;

    // Getters
    const std::vector<std::string>& getXLabels() const { return x_labels_; }
    const std::vector<double>& getYValues() const { return y_values_; }
    std::string getTitle() const { return title_; }
    const std::vector<Color>& getColors() const { return colors_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    float getCameraDistance() const { return camera_distance_; }
    float getCameraAngleX() const { return camera_angle_x_; }
    float getCameraAngleY() const { return camera_angle_y_; }

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

    void setTitle(const std::string& title) {
        if (title.empty()) {
            throw ChartasticError("Title cannot be empty");
        }
        title_ = title;
    }

    void setColors(const std::vector<Color>& colors) {
        if (colors.empty()) {
            throw ChartasticError("Colors vector cannot be empty");
        }
        colors_ = colors;
    }

    void setWidth(int width) {
        if (width <= 0) {
            throw ChartasticError("Width must be positive, got " + std::to_string(width));
        }
        if (width < 400) {
            throw ChartasticError("Width too small for 3D rendering (minimum 400), got " + std::to_string(width));
        }
        width_ = width;
    }

    void setHeight(int height) {
        if (height <= 0) {
            throw ChartasticError("Height must be positive, got " + std::to_string(height));
        }
        if (height < 300) {
            throw ChartasticError("Height too small for 3D rendering (minimum 300), got " + std::to_string(height));
        }
        height_ = height;
    }

    void setWindowSize(int width, int height) {
        setWidth(width);
        setHeight(height);
    }

    void setCameraDistance(float distance) {
        if (distance <= 0.0f) {
            throw ChartasticError("Camera distance must be positive, got " + std::to_string(distance));
        }
        camera_distance_ = distance;
    }

    void setCameraAngleX(float angle) { camera_angle_x_ = angle; }
    void setCameraAngleY(float angle) { camera_angle_y_ = angle; }
};

}

#endif // CHARTASTIC_3D_BAR_HPP
