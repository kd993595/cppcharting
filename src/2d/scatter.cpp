#include <chartastic/2d/scatter.hpp>

namespace chartastic {

void Scatter::show() const{
  // Initalize all variables for rendering
  std::vector<std::tuple<int, int, std::string>> x_axis;
  std::vector<std::tuple<int, int, std::string>> y_axis;
  
  double diff_x = std::round((max_x - min_x) / 10);
  double diff_y = std::round((max_y - min_y) / 10);

  for(double cur_diff=min_x;  cur_diff < max_x; cur_diff += diff_x){
    std::string x_num = std::to_string(std::lround(cur_diff));
    x_axis.push_back({GetScreenX(cur_diff), height_ - top_pad + 10, x_num});
  }
  x_axis.push_back({GetScreenX(max_x), height_ - top_pad + 10, std::to_string(static_cast<int>(max_x))});

  for(double cur_diff=min_y; cur_diff < max_y; cur_diff += diff_y){
    std::string y_num = std::to_string(std::lround(cur_diff));
    y_axis.push_back({left_pad - 50, GetScreenY(cur_diff)-10, y_num});
  }
  y_axis.push_back({left_pad - 50, GetScreenY(max_y)-10, std::to_string(static_cast<int>(max_y))});


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

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);

    
    // Draw Points
    for(size_t i=0;i<points.size();i++){
      for(size_t j=0;j<points[i].size();j++){
        if(point_size[i].empty()){
          DrawCircle(GetScreenX(points[i][j].first), GetScreenY(points[i][j].second), 6, graph_colors[i]);
        }else{
          DrawCircle(GetScreenX(points[i][j].first), GetScreenY(points[i][j].second), point_size[i][j],graph_colors[i]);
        }
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
      DrawTextPro(default_font, y_axis_name.c_str(), (Vector2){10,static_cast<float>(height_ / 2)}, (Vector2){static_cast<float>(MeasureText(y_axis_name.c_str(), 25)/2), 0}, 270, 25, 10, BLACK);
    }

    EndDrawing();
  }

  CloseWindow();
}

void Scatter::exportAs(const std::string& filename) const {
    // Validate filename
    if (filename.empty()) {
        throw ChartasticError("Export filename cannot be empty");
    }
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".png") {
        throw ChartasticError("Export filename must end with .png extension");
    }

    // Validate we have data to export
    if (points.empty()) {
        throw ChartasticError("Cannot export plot with no data");
    }

    std::vector<std::tuple<int, int, std::string>> x_axis;
    std::vector<std::tuple<int, int, std::string>> y_axis;
    
    double diff_x = std::round((max_x - min_x) / 10);
    double diff_y = std::round((max_y - min_y) / 10);

    for(double cur_diff=min_x;  cur_diff < max_x; cur_diff += diff_x){
      std::string x_num = std::to_string(std::lround(cur_diff));
      x_axis.push_back({GetScreenX(cur_diff), height_ - top_pad + 10, x_num});
    }
    x_axis.push_back({GetScreenX(max_x), height_ - top_pad + 10, std::to_string(static_cast<int>(max_x))});

    for(double cur_diff=min_y; cur_diff < max_y; cur_diff += diff_y){
      std::string y_num = std::to_string(std::lround(cur_diff));
      y_axis.push_back({left_pad - 50, GetScreenY(cur_diff)-10, y_num});
    }
    y_axis.push_back({left_pad - 50, GetScreenY(max_y)-10, std::to_string(static_cast<int>(max_y))});


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

    // Set up hidden window for offscreen rendering
    SetConfigFlags(FLAG_WINDOW_HIDDEN);
    InitWindow(width_, height_, "Hidden");
    Font default_font = GetFontDefault();


    // Create render texture for offscreen rendering
    RenderTexture2D target = LoadRenderTexture(width_, height_);

    // Render to texture
    BeginTextureMode(target);
    ClearBackground(RAYWHITE);

    DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);

    
    // Draw Points
    for(size_t i=0;i<points.size();i++){
      for(size_t j=0;j<points[i].size();j++){
        if(point_size[i].empty()){
          DrawCircle(GetScreenX(points[i][j].first), GetScreenY(points[i][j].second), 6, graph_colors[i]);
        }else{
          DrawCircle(GetScreenX(points[i][j].first), GetScreenY(points[i][j].second), point_size[i][j],graph_colors[i]);
        }
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
      DrawTextPro(default_font, y_axis_name.c_str(), (Vector2){10,static_cast<float>(height_ / 2)}, (Vector2){static_cast<float>(MeasureText(y_axis_name.c_str(), 25)/2), 0}, 270, 25, 10, BLACK);
    }    
    
    EndTextureMode();

    // Export the texture to an image file
    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);  // Flip because texture coordinates are inverted

    if (!ExportImage(image, filename.c_str())) {
        UnloadImage(image);
        UnloadRenderTexture(target);
        CloseWindow();
        throw ChartasticError("Failed to export image to file: " + filename);
    }

    // Clean up
    UnloadImage(image);
    UnloadRenderTexture(target);
    CloseWindow();
}
  
}
