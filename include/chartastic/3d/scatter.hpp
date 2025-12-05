#ifndef CHARTASTIC_3D_SCATTER_HPP
#define CHARTASTIC_3D_SCATTER_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <chartastic/core/concepts.hpp>
#include <chartastic/core/error.hpp>
#include <chartastic/core/colors.hpp>
#include <raylib.h>

namespace chartastic {

class ScatterPlot3D {
private:
    std::vector<std::string> labels_;
    std::vector<std::vector<float>> x_values_;
    std::vector<std::vector<float>> y_values_;
    std::vector<std::vector<float>> z_values_;
    std::string title_ = "3D Scatter Plot";
    std::vector<Color> colors_;
    int width_ = 1200;
    int height_ = 800;

    // Camera settings
    float camera_distance_ = 15.0f;
    float camera_angle_x_ = 45.0f;
    float camera_angle_y_ = 45.0f;

public:
    ScatterPlot3D() = default;

    ScatterPlot3D(std::string t) : title_(t) {}

    void show() const;

    // Getters
    std::string getTitle() const { return title_; }
    const std::vector<Color>& getColors() const { return colors_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    float getCameraDistance() const { return camera_distance_; }
    float getCameraAngleX() const { return camera_angle_x_; }
    float getCameraAngleY() const { return camera_angle_y_; }

    // Setters
  
  template <NumericIterator Iter>
  void addSeries(Iter x_begin, Iter x_end, Iter y_begin, Iter y_end, Iter z_begin, Iter z_end, std::string name="", Color series_color = (Color){0}){
    if(x_begin == x_end || y_begin == y_end || z_begin == z_end){
      throw ChartasticError("input iterators cannot be empty must contain at least one value");
    }

    std::vector<float> temp_x_val;
    std::vector<float> temp_y_val;
    std::vector<float> temp_z_val;
    while(x_begin != x_end){
      if(z_begin == z_end || y_begin == y_end)
        throw ChartasticError("all input must be of equal length to each other");

      temp_x_val.push_back(static_cast<float>(*x_begin));
      temp_y_val.push_back(static_cast<float>(*y_begin));
      temp_z_val.push_back(static_cast<float>(*z_begin));

      ++x_begin;
      ++y_begin;
      ++z_begin;
    }

    if(y_begin != y_end || z_begin != z_end)
      throw ChartasticError("input iterators must be of equal length to each other");
      
    // if(series_color == (Color){0,0,0,0}){
    //   colors_.push_back(p1[colors_.size()]);
    // }else{
    //   colors_.push_back(series_color);
    // }
    colors_.push_back(p1[colors_.size()]);
    if(name.empty()){
      std::string tempstr = "Series ";
      tempstr += 65 + x_values_.size();
      labels_.push_back(std::move(tempstr));
    }else{
      labels_.push_back(name);
    }
    x_values_.push_back(temp_x_val);
    y_values_.push_back(temp_y_val);
    z_values_.push_back(temp_z_val);
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

#endif // CHARTASTIC_3D_SCATTER_HPP
