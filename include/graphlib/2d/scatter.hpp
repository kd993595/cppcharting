#ifndef GRAPHLIB_2D_SCATTER
#define GRAPHLIB_2D_SCATTER

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


template<typename T>
concept ForwardIteratorNumeric = std::forward_iterator<T> && std::is_integral<typename std::iterator_traits<T>::value_type>::value;


namespace graphlib {

class Scatter{
  std::string title;
  std::vector<std::pair<int, int>> points;
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
  static const int top_pad = 100;
  static const int bottom_pad = 80;

  int GetScreenX(double x){
    double x_lerp = (double)(x - min_x) / (double)(max_x - min_x) * (double)(screenWidth - right_pad - left_pad) + (double)left_pad;
    return static_cast<int>(std::lround(x_lerp));
  }
  
  int GetScreenY(double y){
    double y_lerp = (double)(y - min_y) / (double)(max_y - min_y) * (double)(screenHeight - top_pad - bottom_pad) + (double)bottom_pad;
    double y_flip = (double)(screenHeight - bottom_pad - 10) - (double)(y_lerp - bottom_pad);
    return static_cast<int>(std::lround(y_flip));
  }

public:
  explicit Scatter(std::string t, int minX, int maxX, int minY, int maxY) : 
    title(t), points(), x_axis(), y_axis(), min_x(minX), max_x(maxX), min_y(minY), max_y(maxY)
  {
    double diff_x = std::round((double)(maxX - minX) / 10);
    double diff_y = std::round((double)(maxY - minY) / 10);

    for(size_t i=0;i<9;i++){
      std::string x_num = std::to_string(std::lround((double)minX + i*diff_x));
      x_axis.push_back({GetScreenX((double)min_x + i*diff_x), screenHeight - bottom_pad + 10, x_num});
    }
    x_axis.push_back({GetScreenX(max_x), screenHeight - bottom_pad + 10, std::to_string(maxX)});

    for(size_t i=0;i<9;i++){
      std::string y_num = std::to_string(std::lround((double)minY + i*diff_y));
      y_axis.push_back({left_pad - 25, GetScreenY((double)min_y + i*diff_y), y_num});
    }
    y_axis.push_back({left_pad - 25, GetScreenY(max_y), std::to_string(maxY)});
  }

  template<ForwardIteratorNumeric Iter>
  void addScatter(Iter x_begin, Iter x_end, Iter y_begin, Iter y_end){
    if(x_begin == x_end || y_begin == y_end)
      throw std::length_error("cannot input empty iterators");

    while(x_begin != x_end){
      if(y_begin == y_end){
        throw std::length_error("y vector does not match x vector length");
      }

      points.push_back({GetScreenX((double)*x_begin), GetScreenY((double)*y_begin)});

      ++x_begin;
      ++y_begin;
    }
    if(y_begin != y_end){
      throw std::length_error("x vector smaller than y vector");
    }
  }

  void show() const{
    // const int screenWidth = 1600;
    // const int screenHeight = 1200;
    //
    // const int left_pad = 100;
    // const int right_pad = 50;
    // const int top_pad = 100;
    // const int bottom_pad = 80;

    InitWindow(screenWidth, screenHeight, "Chartastic");
    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);

      DrawText(title.c_str(), screenWidth / 2 - MeasureText(title.c_str(), 30) / 2, 20, 30, BLACK);

      
      // Draw Points
      for(size_t i=0;i<points.size();i++){
       DrawCircle(points[i].first, points[i].second, 10, SKYBLUE);
      }
      
      
      // Draw axises
      DrawLine(left_pad, screenHeight - bottom_pad, screenWidth - right_pad, screenHeight - bottom_pad, BLACK); // x axis line
      DrawLine(left_pad, screenHeight - bottom_pad, left_pad, top_pad, BLACK); // y axis line

      // draw numbers on axises
      for(size_t i=0;i<x_axis.size();i++){
        DrawText(std::get<2>(x_axis[i]).c_str(), std::get<0>(x_axis[i]), std::get<1>(x_axis[i]), 18, BLACK);
      }
      for(size_t i=0;i<y_axis.size();i++){
        DrawText(std::get<2>(y_axis[i]).c_str(), std::get<0>(y_axis[i]), std::get<1>(y_axis[i]), 18, BLACK);
      }

      EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
  }

};

}
#endif // Scatter Plot header
