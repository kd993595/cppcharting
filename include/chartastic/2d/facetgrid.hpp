#ifndef CHARTASTIC_2D_FACETGRID
#define CHARTASTIC_2D_FACETGRID

#include <raylib.h>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <tuple>
#include <cstdio>
#include <chartastic/core/concepts.hpp>


namespace chartastic {

struct smallGrid {
  std::string name;
  int x_start;
  int y_start;
  int width;
  int height;
  bool active;
};

class Facetgrid{
  std::string title;
  std::vector<smallGrid> grids;
  std::vector<std::vector<std::pair<int, int>>> points;
  std::vector<std::vector<std::tuple<int, int, std::string>>> x_axis;
  std::vector<std::vector<std::tuple<int, int, std::string>>> y_axis;
  int min_x;
  int max_x;
  int min_y;
  int max_y;
  size_t num_grids;
  size_t cur_grid = 0;
  static const int screenWidth = 1600;
  static const int screenHeight = 1200;
  static const int left_pad = 40;
  static const int right_pad = 40;
  static const int top_pad = 100;
  static const int bottom_pad = 40;
  static const int grid_top_pad = 30;
  static const int grid_bottom_pad = 20;
  static const int grid_left_pad = 30;
  static const int grid_right_pad = 20;

  int GetScreenX(double x, int iGrid){
    int x_end = grids[iGrid].x_start + grids[iGrid].width;
    int t_max = x_end - grid_right_pad;
    int t_min = grids[iGrid].x_start + grid_left_pad;
    double x_lerp = static_cast<double>(x - min_x) / static_cast<double>(max_x - min_x) * static_cast<double>(t_max - t_min) + static_cast<double>(t_min);
    return static_cast<int>(std::lround(x_lerp));
  }
  
  int GetScreenY(double y, int iGrid){
    int y_end = grids[iGrid].y_start + grids[iGrid].height;
    int t_max = y_end - grid_top_pad;
    int t_min = grids[iGrid].y_start + grid_bottom_pad;
    double y_lerp = static_cast<double>(y - min_y) / static_cast<double>(max_y - min_y) * static_cast<double>(t_max - t_min) + static_cast<double>(t_min);
    // double y_flip = (double)(y_end - grid_bottom_pad) - (double)(y_lerp  - grid_top_pad);
    double y_flip = static_cast<double>(t_max) - y_lerp + static_cast<double>(t_min);
    return static_cast<int>(std::lround(y_flip));
  }

public:
  explicit Facetgrid(std::string t, int minX, int maxX, int minY, int maxY, int maxGrids) : 
    title(t), grids(), points(), x_axis(), y_axis(), min_x(minX), max_x(maxX), min_y(minY), max_y(maxY)
  {
    if(maxGrids > 9)
      throw std::invalid_argument("Chartastic Error: max number of grids cannot be greater than 8");
    int n_grids, cols, rows;
    double x_divide, y_divide;
    if(maxGrids > 6){
      n_grids = 9;
      rows = cols = 3;
      x_divide = 3;
      y_divide = 3;
    }else if(maxGrids > 4){
      n_grids = 6;
      rows = 2;
      cols = 3;
      x_divide = 3;
      y_divide = 2;
    }else if(maxGrids > 2){
      n_grids = 4;
      rows = cols = 2;
      x_divide = 2;
      y_divide = 2;
    }else if(maxGrids > 1){
      n_grids = 2;
      rows = 1;
      cols = 2;
      x_divide = 2;
      y_divide = 1;
    }else{
      n_grids = 1;
      rows = cols = 1;
      x_divide = 1;
      y_divide = 1;
    }
    num_grids = n_grids;
    double diff_x = std::round(static_cast<double>(maxX - minX) / 10);
    double diff_y = std::round(static_cast<double>(maxY - minY) / 10);

    for(size_t i=0;i<num_grids;i++){
      smallGrid temp_grid;
      temp_grid.name = "Series ";
      temp_grid.name += 65+i;
      temp_grid.active = false;
      int x_size = std::lround(static_cast<double>(screenWidth - left_pad - right_pad) / x_divide);
      int y_size = std::lround(static_cast<double>(screenHeight - top_pad - bottom_pad) / y_divide);
      int cur_row = static_cast<int>(i) % rows;
      int cur_col = static_cast<int>(i) / rows;
      temp_grid.width = x_size;
      temp_grid.height = y_size;
      temp_grid.x_start = cur_col * x_size + left_pad;
      temp_grid.y_start = cur_row * y_size + top_pad;
      std::printf("Grid: %d (col=%d,row=%d), xstart: %d, ystart: %d, width = %d, height = %d\n", i,cur_col,cur_row, temp_grid.x_start, temp_grid.y_start, temp_grid.width, temp_grid.height);

      grids.push_back(temp_grid);
    } 

    for(size_t i=0;i<num_grids;i++){
      std::vector<std::tuple<int, int, std::string>> temp_x_axis;
      std::vector<std::tuple<int, int, std::string>> temp_y_axis;

      for(double cur_diff=min_x; cur_diff < max_x; cur_diff += diff_x){
        std::string x_num = std::to_string(std::lround(cur_diff));
        temp_x_axis.push_back({GetScreenX(cur_diff, i), grids[i].y_start + grids[i].height - grid_bottom_pad, x_num});
      }
      temp_x_axis.push_back({GetScreenX(max_x, i), grids[i].y_start + grids[i].height - grid_bottom_pad, std::to_string(max_x)});
      for(double cur_diff=min_y; cur_diff < max_y; cur_diff += diff_y){
        std::string y_num = std::to_string(std::lround(cur_diff));
        temp_y_axis.push_back({grids[i].x_start + grid_left_pad - 28, GetScreenY(cur_diff, i) - 3, y_num});
      }
      temp_y_axis.push_back({grids[i].x_start + grid_left_pad - 28, GetScreenY(max_y, i) - 3, std::to_string(max_y)});

      x_axis.push_back(temp_x_axis);
      y_axis.push_back(temp_y_axis);
    }

    /*for(double cur_diff=min_x;  cur_diff < max_x; cur_diff += diff_x){
      std::string x_num = std::to_string(std::lround(cur_diff));
      x_axis.push_back({GetScreenX(cur_diff), screenHeight - bottom_pad + 10, x_num});
    }
    x_axis.push_back({GetScreenX(max_x), screenHeight - bottom_pad + 10, std::to_string(maxX)});

    for(double cur_diff=min_y; cur_diff < max_y; cur_diff += diff_y){
      std::string y_num = std::to_string(std::lround(cur_diff));
      y_axis.push_back({left_pad - 25, GetScreenY(cur_diff), y_num});
    }
    y_axis.push_back({left_pad - 25, GetScreenY(max_y), std::to_string(maxY)});*/
  }

  template<chartastic::NumericIterator Iter>
  void addGrid(Iter x_begin, Iter x_end, Iter y_begin, Iter y_end, std::string name = ""){
    if(cur_grid == num_grids)
      throw std::invalid_argument("Chartastic Error: cannot add any more series exceeds max number grids.");
    if(x_begin == x_end || y_begin == y_end)
      throw std::length_error("Chartastic Error: cannot input empty iterators.");

    std::vector<std::pair<int,int>> temp_points;
    while(x_begin != x_end){
      if(y_begin == y_end){
        throw std::length_error("Chartastic Error: y vector smaller than x vector length.");
      }

      temp_points.push_back({GetScreenX((double)*x_begin, cur_grid), GetScreenY((double)*y_begin, cur_grid)});

      ++x_begin;
      ++y_begin;
    }

    if(y_begin != y_end){
      throw std::length_error("Chartastic Error: x vector smaller than y vector length.");
    }

    if(!name.empty())
      grids[cur_grid].name = name;
    grids[cur_grid].active = true;
    cur_grid++;
    points.push_back(temp_points);
  }

  void show() const{
    InitWindow(screenWidth, screenHeight, "Chartastic");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);

      DrawText(title.c_str(), screenWidth / 2 - MeasureText(title.c_str(), 30) / 2, 20, 30, BLACK);

      
      // Draw Points
      for(size_t i=0;i<points.size();i++){
        for(size_t j=0;j<points[i].size();j++){
          DrawCircle(points[i][j].first, points[i][j].second, 6, DARKGRAY);
        }
      }
      
      // Draw axises
      for(size_t i=0;i<num_grids;i++){
        // if(!grids[i].active)
        //   continue;
        DrawLine(grids[i].x_start + grid_left_pad, grids[i].y_start + grids[i].height - grid_bottom_pad, grids[i].x_start + grids[i].width - grid_right_pad, grids[i].y_start + grids[i].height - grid_bottom_pad, BLACK); //x axis
        DrawLine(grids[i].x_start + grid_left_pad, grids[i].y_start + grids[i].height - grid_bottom_pad, grids[i].x_start + grid_left_pad, grids[i].y_start + grid_top_pad, BLACK); // y axis
        DrawText(grids[i].name.c_str(), grids[i].x_start + (grids[i].width / 2) - MeasureText(grids[i].name.c_str(), 20) / 2, grids[i].y_start, 20, BLACK);
        // DrawRectangleLines(grids[i].x_start, grids[i].y_start, grids[i].width, grids[i].height, RED); // debugging
      }

      // draw numbers on axises
      for(size_t i=0;i<x_axis.size();i++){
        // if(!grids[i].active)
        //   continue;
        for(size_t j=0;j<x_axis[i].size();j++){
          DrawText(std::get<2>(x_axis[i][j]).c_str(), std::get<0>(x_axis[i][j]), std::get<1>(x_axis[i][j]), 18, BLACK);
        }
      }
      for(size_t i=0;i<y_axis.size();i++){
        // if(!grids[i].active)
        //   continue;
        for(size_t j=0;j<y_axis[i].size();j++){
          DrawText(std::get<2>(y_axis[i][j]).c_str(), std::get<0>(y_axis[i][j]), std::get<1>(y_axis[i][j]), 18, BLACK);
        }
      }

      EndDrawing();
    }

    CloseWindow();
  }

};

}
#endif // CHARTASTIC_2D_FACETGRID
