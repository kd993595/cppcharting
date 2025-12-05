#ifndef GRAPHLIB_2D_LINE
#define GRAPHLIB_2D_LINE

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
#include <chartastic/core/concepts.hpp>
#include <chartastic/core/colors.hpp>
#include <chartastic/2d/plot.hpp>

namespace chartastic {

class Line : public Plot{
  std::string x_axis_name;
  std::string y_axis_name;
  std::vector<std::vector<std::pair<double, double>>> points;
  std::vector<std::string> names;
  // std::vector<std::tuple<int, int, std::string>> x_axis;
  // std::vector<std::tuple<int, int, std::string>> y_axis;
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
  // std::vector<std::pair<int, int>> legend;
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
  Line(std::string t, double minX, double maxX, double minY, double maxY, std::string x_name = "",std::string y_name = "",bool show_legend = false) : 
    x_axis_name(x_name), y_axis_name(y_name), points(), names(), min_x(minX), max_x(maxX), min_y(minY), max_y(maxY), show_legend(show_legend)
  {
    title_ = t;
    if(show_legend){
      top_pad = 140;
    }
  }

  template<chartastic::NumericIterator Iter>
  void addLine(Iter x_begin, Iter x_end, Iter y_begin, Iter y_end, std::string name = ""){
    if(points.size() >= 12)
      throw ChartasticError("Chartastic Error: why do you have more than 12 series");
    if(x_begin == x_end || y_begin == y_end)
      throw ChartasticError("cannot input empty iterators");

    std::vector<std::pair<double,double>> temp_points;
    double previous = static_cast<double>(*x_begin);
    temp_points.push_back({static_cast<double>(*x_begin), static_cast<double>(*y_begin)});

    ++x_begin;
    ++y_begin;
    if(x_begin == x_end || y_begin == y_end)
      throw ChartasticError("line plot must have at least 2 points");

    while(x_begin != x_end){
      if(y_begin == y_end){
        throw ChartasticError("y vector does not match x vector length");
      }

      double temp_x = *x_begin;
      if(temp_x <= previous)
        throw ChartasticError("x variables must be increasing cannot have line go backwards");
      previous = temp_x;

      temp_points.push_back({temp_x, static_cast<double>(*y_begin)});

      ++x_begin;
      ++y_begin;
    }
    if(y_begin != y_end){
      throw ChartasticError("x vector smaller than y vector must be equal length");
    }
    if(name.empty()){
      std::string temp_name = "Series ";
      temp_name += 65 + points.size();
      names.push_back(std::move(temp_name));
    }else{
      names.push_back(name);
    }
    points.push_back(temp_points);
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
#endif // GRAPHLIB_2D_LINE
