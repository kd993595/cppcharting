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

namespace chartastic {

class Line{
  std::string title;
  std::string x_axis_name;
  std::string y_axis_name;
  std::vector<std::vector<std::pair<int, int>>> points;
  std::vector<std::string> names;
  std::vector<std::tuple<int, int, std::string>> x_axis;
  std::vector<std::tuple<int, int, std::string>> y_axis;
  int min_x;
  int max_x;
  int min_y;
  int max_y;
  static const int screenWidth = 1600;
  static const int screenHeight = 1200;
  static const int left_pad = 100;
  static const int right_pad = 50;
  int top_pad = 100;
  int bottom_pad = 80;
  std::vector<Color> graph_colors;
  bool show_legend;
  std::vector<std::pair<int, int>> legend;
  std::array<Color, 12>& palette = p1;

  int GetScreenX(double x){
    int t_max = screenWidth - right_pad;
    int t_min = left_pad;
    double x_lerp = static_cast<double>(x - min_x) / static_cast<double>(max_x - min_x) * static_cast<double>(t_max - t_min) + static_cast<double>(t_min);
    return static_cast<int>(std::lround(x_lerp));
  }
  
  int GetScreenY(double y){
    int t_max = screenHeight - top_pad;
    int t_min = bottom_pad;
    double y_lerp = static_cast<double>(y - min_y) / static_cast<double>(max_y - min_y) * static_cast<double>(t_max - t_min) + static_cast<double>(t_min);
    double y_flip = static_cast<double>(t_max) - y_lerp + static_cast<double>(t_min);
    return static_cast<int>(std::lround(y_flip));
  }

  void RecalculateLegend(){
    if(!show_legend) return;
    const int offset = screenWidth / 50;
    legend.clear();
    if(points.size() > 6){
      double sizing = static_cast<double>(screenWidth - offset) / 6;
      for(size_t i=0;i<6;i++){
        std::pair<int,int> legend_point = {static_cast<int>(std::lround(sizing * i) + offset), screenHeight - 40};
        legend.push_back(legend_point);
      }
      for(size_t i=6;i<points.size();i++){
        std::pair<int,int> legend_point = {static_cast<int>(std::lround(sizing * (i-6)) + offset), screenHeight - 20};
        legend.push_back(legend_point);
      }
    }else{
      double sizing = static_cast<double>(screenWidth - offset) / points.size();
      for(size_t i=0;i<points.size();i++){
        std::pair<int,int> legend_point = {static_cast<int>(std::lround(sizing * (i)) + offset), screenHeight - 20};
        legend.push_back(legend_point);
      }
    }
  }

public:
  explicit Line(std::string t, int minX, int maxX, int minY, int maxY, std::string x_name = "",std::string y_name = "",bool show_legend = false, ColorPalette color_palette = ColorPalette::palette1) : 
    title(t), x_axis_name(x_name), y_axis_name(y_name), points(), names(), x_axis(), y_axis(), min_x(minX), max_x(maxX), min_y(minY), max_y(maxY), show_legend(show_legend), legend()
  {
    if(show_legend){
      top_pad = 140;
    }
    switch(color_palette){
      case ColorPalette::palette1: palette = p1; break;
      case ColorPalette::palette2: palette = p2; break;
      case ColorPalette::palette3: palette = p3; break;
    }
    double diff_x = std::round((double)(maxX - minX) / 10);
    double diff_y = std::round((double)(maxY - minY) / 10);

    for(double cur_diff=min_x;  cur_diff < max_x; cur_diff += diff_x){
      std::string x_num = std::to_string(std::lround(cur_diff));
      x_axis.push_back({GetScreenX(cur_diff), screenHeight - top_pad + 10, x_num});
    }
    x_axis.push_back({GetScreenX(max_x), screenHeight - top_pad + 10, std::to_string(maxX)});

    for(double cur_diff=min_y; cur_diff < max_y; cur_diff += diff_y){
      std::string y_num = std::to_string(std::lround(cur_diff));
      y_axis.push_back({left_pad - 50, GetScreenY(cur_diff) - 10, y_num});
    }
    y_axis.push_back({left_pad - 50, GetScreenY(max_y) - 10, std::to_string(maxY)});
  }

  template<chartastic::NumericIterator Iter>
  void addLine(Iter x_begin, Iter x_end, Iter y_begin, Iter y_end, std::string name = ""){
    if(points.size() >= 12)
      throw std::invalid_argument("Chartastic Error: why do you have more than 12 series");
    if(x_begin == x_end || y_begin == y_end)
      throw std::length_error("cannot input empty iterators");

    std::vector<std::pair<int,int>> temp_points;
    double previous = *x_begin;
    temp_points.push_back({GetScreenX((double)*x_begin), GetScreenY((double)*y_begin)});

    ++x_begin;
    ++y_begin;
    if(x_begin == x_end || y_begin == y_end)
      throw std::length_error("line plot must have at least 2 points");

    while(x_begin != x_end){
      if(y_begin == y_end){
        throw std::length_error("y vector does not match x vector length");
      }

      double temp_x = *x_begin;
      if(temp_x <= previous)
        throw std::invalid_argument("x variables must be increasing cannot have line go backwards");
      previous = temp_x;

      temp_points.push_back({GetScreenX(temp_x), GetScreenY((double)*y_begin)});

      ++x_begin;
      ++y_begin;
    }
    if(y_begin != y_end){
      throw std::length_error("x vector smaller than y vector must be equal length");
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
    RecalculateLegend();
  }

  void show() const {
    InitWindow(screenWidth, screenHeight, "Chartastic");
    SetTargetFPS(60);
    Font default_font = GetFontDefault();

    while (!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);

      DrawText(title.c_str(), screenWidth / 2 - MeasureText(title.c_str(), 30) / 2, 20, 30, BLACK);
      
      // Draw Lines
      for(size_t i=0;i<points.size();i++){
        for(size_t j=0;j<points[i].size()-1;j++){
          Vector2 startpos = {static_cast<float>(points[i][j].first), static_cast<float>(points[i][j].second)};
          Vector2 endpos = {static_cast<float>(points[i][j+1].first), static_cast<float>(points[i][j+1].second)};
          DrawLineEx(startpos, endpos, 5, graph_colors[i]);
        }
      }
      
      
      // Draw axises
      DrawLine(left_pad, screenHeight - top_pad, screenWidth - right_pad, screenHeight - top_pad, BLACK); // x axis line
      DrawLine(left_pad, screenHeight - top_pad, left_pad, bottom_pad, BLACK); // y axis line

      // draw numbers on axises
      for(size_t i=0;i<x_axis.size();i++){
        DrawText(std::get<2>(x_axis[i]).c_str(), std::get<0>(x_axis[i]), std::get<1>(x_axis[i]), 18, BLACK);
      }
      for(size_t i=0;i<y_axis.size();i++){
        DrawText(std::get<2>(y_axis[i]).c_str(), std::get<0>(y_axis[i]), std::get<1>(y_axis[i]), 18, BLACK);
      }

      for(size_t i=0;i<legend.size();i++){
        DrawCircle(legend[i].first, legend[i].second, 10, graph_colors[i]);
        DrawText(names[i].c_str(), legend[i].first + 11, legend[i].second - 10, 20, BLACK);
      }

      if(!x_axis_name.empty()){
        DrawText(x_axis_name.c_str(), screenWidth / 2 - MeasureText(x_axis_name.c_str(), 25) / 2, screenHeight - top_pad + 40, 25, BLACK);
      }
      if(!y_axis_name.empty()){
        DrawTextPro(default_font, y_axis_name.c_str(), {10,screenHeight / 2}, {static_cast<float>(MeasureText(y_axis_name.c_str(), 25)/2), 0}, 270, 25, 10, BLACK);
      }

      EndDrawing();
    }

    CloseWindow();
  }

};

}
#endif // GRAPHLIB_2D_LINE
