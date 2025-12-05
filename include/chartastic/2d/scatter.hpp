#ifndef CHARTASTIC_2D_SCATTER
#define CHARTASTIC_2D_SCATTER

#include <raylib.h>
#include <string>
#include <vector>
#include <concepts>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <tuple>
#include <array>
#include <chartastic/core/concepts.hpp>
#include <chartastic/core/colors.hpp>
#include <chartastic/2d/plot.hpp>
#include <chartastic/core/error.hpp>


namespace chartastic {

class Scatter : public Plot{
  std::vector<std::vector<std::pair<double, double>>> points;
  std::vector<std::vector<int>> point_size;
  std::vector<std::string> names;
  double min_x;
  double max_x;
  double min_y;
  double max_y;
  static const int left_pad = 100;
  static const int right_pad = 50;
  int top_pad = 100;
  int bottom_pad = 80;
  std::vector<Color> graph_colors;
  bool show_legend;
  std::string x_axis_name;
  std::string y_axis_name;
  std::array<Color, 12>& palette = p1;

  int GetScreenX(double x) const{
    int t_max = width_ - right_pad;
    int t_min = left_pad;
    double x_lerp = static_cast<double>(x - min_x) / static_cast<double>(max_x - min_x) * static_cast<double>(t_max - t_min) + static_cast<double>(t_min);
    return static_cast<int>(std::lround(x_lerp));
  }
  
  int GetScreenY(double y) const{
    int t_max = height_ - top_pad;
    int t_min = bottom_pad;
    double y_lerp = static_cast<double>(y - min_y) / static_cast<double>(max_y - min_y) * static_cast<double>(t_max - t_min) + static_cast<double>(t_min);
    double y_flip = static_cast<double>(t_max) - y_lerp + static_cast<double>(t_min);
    return static_cast<int>(std::lround(y_flip));
  }

public:
  Scatter(){
    title_ = "Scatter Plot";
  }
  Scatter(std::string t, double minX, double maxX, double minY, double maxY, std::string x_name = "",std::string y_name = "",bool show_legend = false) : 
    points(), point_size(), names(), min_x(minX), max_x(maxX), min_y(minY), max_y(maxY), graph_colors(), x_axis_name(x_name), y_axis_name(y_name), show_legend(show_legend)
  {
    title_ = t;
    if(show_legend){
      top_pad = 140;
    }
  }

  template<NumericIterator Iter>
  void addScatter(Iter x_begin, Iter x_end, Iter y_begin, Iter y_end, std::string name = ""){
    if(points.size() >= 12)
      throw ChartasticError("Chartastic Error: why do you have more than 12 series?");
    if(x_begin == x_end || y_begin == y_end)
      throw std::length_error("cannot input empty iterators");

    std::vector<std::pair<double, double>> temp_points;
    while(x_begin != x_end){
      if(y_begin == y_end){
        throw std::length_error("y vector does not match x vector length");
      }

      temp_points.push_back({static_cast<double>(*x_begin), static_cast<double>(*y_begin)});

      ++x_begin;
      ++y_begin;
    }
    if(y_begin != y_end){
      throw std::length_error("x vector smaller than y vector");
    }
    if(name.empty()){
      std::string temp_name = "Series ";
      temp_name += 65 + points.size();
      names.push_back(std::move(temp_name));
    }else{
      names.push_back(name);
    }
    points.push_back(temp_points);
    graph_colors.push_back(palette[graph_colors.size()]);
    std::vector<int> empty_size;
    point_size.push_back(empty_size);
  }

  template<NumericIterator Iter>
  void addScatter(Iter x_begin, Iter x_end, Iter y_begin, Iter y_end, Iter size_begin, Iter size_end, std::string name = ""){
    if(points.size() >= 12)
      throw std::invalid_argument("Chartastic Error: why do you have more than 12 series");
    if(x_begin == x_end || y_begin == y_end || size_begin == size_end)
      throw std::length_error("Chartastic Error: cannot input empty iterators.");

    std::vector<std::pair<double, double>> temp_points;
    std::vector<int> sizes;
    while(x_begin != x_end){
      if(y_begin == y_end){
        throw std::length_error("Chartastic Error: y vector does not match x vector length.");
      }
      if(size_begin == size_end){
        throw std::length_error("Chartastic Error: size vector does not match x vector length.");
      }

      temp_points.push_back({static_cast<double>(*x_begin), static_cast<double>(*y_begin)});
      sizes.push_back(6 + static_cast<int>(*size_begin));

      ++x_begin;
      ++y_begin;
      ++size_begin;
    }
    if(y_begin != y_end){
      throw ChartasticError("Chartastic Error: x vector smaller than y vector");
    }
    if(size_begin != size_end){
      throw ChartasticError("Chartastic Error: x vector smaller than size vector");
    }
    if(name.empty()){
      std::string temp_name = "Series ";
      temp_name += 65 + points.size();
      names.push_back(std::move(temp_name));
    }else{
      names.push_back(name);
    }
    points.push_back(temp_points);
    point_size.push_back(sizes);
    if(graph_colors.size() < palette.size()){
      graph_colors.push_back(palette[graph_colors.size()]);
    }
  }

  void setColors(const std::vector<Color>& colors) {
    if (colors.empty()) {
      throw ChartasticError("Colors vector cannot be empty");
    }
    graph_colors = colors;
  }

  void setColors(ColorPalette palette){
    graph_colors.resize(12);
    switch(palette){
      case ColorPalette::palette1: std::copy(p1.begin(),p1.end(),graph_colors.begin());
      case ColorPalette::palette2: std::copy(p2.begin(),p2.end(),graph_colors.begin());
      case ColorPalette::palette3: std::copy(p3.begin(),p3.end(),graph_colors.begin());
      case ColorPalette::palette4: std::copy(p4.begin(),p4.end(),graph_colors.begin());
    }
  }

  void setLegend(bool show){
    if(show){
      top_pad = 140;
    }else{
      top_pad = 100;
    }
    show_legend = show;
  }

  void show() const;
  void exportAs(const std::string& filename) const;

};

}
#endif // Scatter Plot header
