#include <chartastic/2d/line.hpp>
#include <chrono>
#include <iostream>

namespace chartastic {
  
void Line::show() const {
  //Initalize variables for rendering
  std::vector<std::tuple<int, int, std::string>> x_axis;
  std::vector<std::tuple<int, int, std::string>> y_axis;

  double diff_x = std::round((double)(max_x - min_x) / 10);
  double diff_y = std::round((double)(max_y - min_y) / 10);

  for(double cur_diff=min_x;  cur_diff < max_x; cur_diff += diff_x){
    std::string x_num = std::to_string(std::lround(cur_diff));
    x_axis.push_back({GetScreenX(cur_diff), height_ - top_pad + 10, x_num});
  }
  x_axis.push_back({GetScreenX(max_x), height_ - top_pad + 10, std::to_string(static_cast<int>(max_x))});

  for(double cur_diff=min_y; cur_diff < max_y; cur_diff += diff_y){
    std::string y_num = std::to_string(std::lround(cur_diff));
    y_axis.push_back({left_pad - 50, GetScreenY(cur_diff) - 10, y_num});
  }
  y_axis.push_back({left_pad - 50, GetScreenY(max_y) - 10, std::to_string(static_cast<int>(max_y))});



  std::vector<std::pair<int, int>> legend;
  if(show_legend){
    const int offset = width_ / 50;
    legend.clear();
    if(points.size() > 6){
      double sizing = static_cast<double>(width_ - offset) / 6;
      for(size_t i=0;i<6;i++){
        std::pair<int,int> legend_point = {static_cast<int>(std::lround(sizing * i) + offset), height_ - 40};
        legend.push_back(legend_point);
      }
      for(size_t i=6;i<points.size();i++){
        std::pair<int,int> legend_point = {static_cast<int>(std::lround(sizing * (i-6)) + offset), height_ - 20};
        legend.push_back(legend_point);
      }
    }else{
      double sizing = static_cast<double>(width_ - offset) / points.size();
      for(size_t i=0;i<points.size();i++){
        std::pair<int,int> legend_point = {static_cast<int>(std::lround(sizing * (i)) + offset), height_ - 20};
        legend.push_back(legend_point);
      }
    }
  }

  InitWindow(width_, height_, "Chartastic");
  SetTargetFPS(60);
  Font default_font = GetFontDefault();

  std::chrono::nanoseconds total_time {0};
  int frames = 0;

  while (!WindowShouldClose())
  {
    auto t_start = std::chrono::system_clock::now();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);
    
    // Draw Lines
    for(size_t i=0;i<points.size();i++){
      for(size_t j=0;j<points[i].size()-1;j++){
        Vector2 startpos = {static_cast<float>(GetScreenX(points[i][j].first)), static_cast<float>(GetScreenY(points[i][j].second))};
        Vector2 endpos = {static_cast<float>(GetScreenX(points[i][j+1].first)), static_cast<float>(GetScreenY(points[i][j+1].second))};
        DrawLineEx(startpos, endpos, 5, graph_colors[i]);
      }
    }
    
    
    // Draw axises
    DrawLine(left_pad, height_ - top_pad, width_ - right_pad, height_ - top_pad, BLACK); // x axis line
    DrawLine(left_pad, height_ - top_pad, left_pad, bottom_pad, BLACK); // y axis line

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
      DrawText(x_axis_name.c_str(), width_ / 2 - MeasureText(x_axis_name.c_str(), 25) / 2, height_ - top_pad + 40, 25, BLACK);
    }
    if(!y_axis_name.empty()){
      DrawTextPro(default_font, y_axis_name.c_str(), {10,static_cast<float>(height_ / 2)}, {static_cast<float>(MeasureText(y_axis_name.c_str(), 25)/2), 0}, 270, 25, 10, BLACK);
    }

    EndDrawing();

    auto t_end = std::chrono::system_clock::now();

    total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
    frames++;

    if (frames == 100){
        std::cout << "MEASUREMENT: Average drawing time for " << points.size() << " elements: " << total_time.count() / 100 << " ns" << '\n';
    }
  }

  CloseWindow();
}

}
