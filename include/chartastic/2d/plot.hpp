#ifndef GRAPHLIB_2D_PLOT_HPP
#define GRAPHLIB_2D_PLOT_HPP
#pragma once
#include <string>
#include <chartastic/core/error.hpp>

namespace chartastic {

class Plot {
protected:
    std::string title_ = "Plot";
    int width_ = 800;
    int height_ = 600;

public:
    virtual ~Plot() = default;

    virtual void show() const = 0;

    // Getters
    std::string getTitle() const { return title_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    // Setters
    void setTitle(const std::string& title) {
        if (title.empty()) {
            throw ChartasticError("Title cannot be empty");
        }
        title_ = title;
    }

    void setWidth(int width) {
        if (width <= 0) {
            throw ChartasticError("Width must be positive, got " + std::to_string(width));
        }
        if (width < 200) {
            throw ChartasticError("Width too small (minimum 200), got " + std::to_string(width));
        }
        width_ = width;
    }

    void setHeight(int height) {
        if (height <= 0) {
            throw ChartasticError("Height must be positive, got " + std::to_string(height));
        }
        if (height < 200) {
            throw ChartasticError("Height too small (minimum 200), got " + std::to_string(height));
        }
        height_ = height;
    }

    void setWindowSize(int width, int height) {
        setWidth(width);
        setHeight(height);
    }
};

} // namespace graphlib
#endif // GRAPHLIB_2D_PLOT_HPP
