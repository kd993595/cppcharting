#include <chartastic/2d/bar.hpp>
#include <chrono>
#include <iostream>
#include <raylib.h>
#include <algorithm>
#include <string>
#include <sstream>

namespace chartastic {

void BarPlot::renderChart() const {
    const int left_padding = 100;
    const int right_padding = 50;
    const int top_padding = 100;
    const int bottom_padding = 80;

    size_t n_bars = std::max<size_t>(1, x_labels_.size());
    double max_y = *std::max_element(y_values_.begin(), y_values_.end());
    if (max_y == 0) max_y = 1;

    ClearBackground(RAYWHITE);

    DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);

    if (orientation_ == Orientation::Vertical) {
        // Vertical bars
        int plot_width = width_ - left_padding - right_padding;
        int bar_width = plot_width / static_cast<int>(n_bars);
        int plot_left = left_padding;
        int plot_bottom = height_ - bottom_padding;
        int plot_height = height_ - top_padding - bottom_padding;

        int total_bar_space = n_bars * bar_width;
        int start_x = left_padding + (plot_width - total_bar_space) / 2;

        // Draw bars
        for (size_t i = 0; i < n_bars; ++i) {
            double scaled_height = y_values_[i] / max_y * plot_height;
            int x = start_x + static_cast<int>(i * bar_width);
            int y = plot_bottom - static_cast<int>(scaled_height);
            Color c = (i < colors_.size()) ? colors_[i] : BLUE;
            int margin = 2;
            DrawRectangle(x + margin, y, bar_width - 2 * margin, static_cast<int>(scaled_height), c);

            // Draw category labels below bar
            int text_width = MeasureText(x_labels_[i].c_str(), 20);
            DrawText(x_labels_[i].c_str(), x + bar_width / 2 - text_width / 2, plot_bottom + 10, 20, BLACK);
        }

        // Draw axes
        DrawLine(plot_left, top_padding, plot_left, plot_bottom, BLACK); // Y-axis
        DrawLine(plot_left, plot_bottom, width_ - right_padding, plot_bottom, BLACK); // X-axis

        // Draw Y-axis ticks and labels
        int n_div = 5;
        for (int i = 0; i <= n_div; ++i) {
            double val = max_y * i / n_div;
            int y_px = plot_bottom - static_cast<int>((val / max_y) * plot_height);
            DrawLine(plot_left - 5, y_px, plot_left, y_px, BLACK);

            // Draw tick label to the left of axis
            std::stringstream ss;
            ss << static_cast<int>(val);
            int text_width = MeasureText(ss.str().c_str(), 20);
            DrawText(ss.str().c_str(), plot_left - text_width - 10, y_px - 10, 20, BLACK);
        }
    } else {
        // Horizontal bars
        int plot_height = height_ - top_padding - bottom_padding;
        int bar_height = plot_height / static_cast<int>(n_bars);
        int plot_left = left_padding;
        int plot_width = width_ - left_padding - right_padding;

        int total_bar_space = n_bars * bar_height;
        int start_y = top_padding + (plot_height - total_bar_space) / 2;

        // Draw bars
        for (size_t i = 0; i < n_bars; ++i) {
            double scaled_width = y_values_[i] / max_y * plot_width;
            int x = plot_left;
            int y = start_y + static_cast<int>(i * bar_height);
            Color c = (i < colors_.size()) ? colors_[i] : BLUE;
            int margin = 2;
            DrawRectangle(x, y, static_cast<int>(scaled_width) - margin, bar_height - 10, c);

            // Draw category labels to the left of bar
            DrawText(x_labels_[i].c_str(), x - 80, y + bar_height / 2 - 10, 20, BLACK);
        }

        // Draw axes on top
        DrawLine(plot_left, top_padding, plot_left, height_ - bottom_padding, BLACK); // Y-axis
        DrawLine(plot_left, height_ - bottom_padding, width_ - right_padding, height_ - bottom_padding, BLACK); // X-axis

        // Draw numeric x-axis ticks
        int n_div = 5;
        for (int i = 0; i <= n_div; ++i) {
            double val = max_y * i / n_div;
            int x_px = plot_left + static_cast<int>((val / max_y) * plot_width);
            DrawLine(x_px, height_ - bottom_padding, x_px, height_ - bottom_padding + 5, BLACK);

            // Draw tick label below axis
            std::stringstream ss;
            ss << static_cast<int>(val);
            DrawText(ss.str().c_str(), x_px - MeasureText(ss.str().c_str(), 20)/2, height_ - bottom_padding + 10, 20, BLACK);
        }
    }
}

void BarPlot::show() const {
    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(60);

    std::chrono::nanoseconds total_time {0};
    int frames = 0;

    while (!WindowShouldClose()) {
        auto t_start = std::chrono::system_clock::now();

        BeginDrawing();
        renderChart();
        EndDrawing();

        auto t_end = std::chrono::system_clock::now();

        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
        frames++;

        if (frames == 100){
            std::cout << "MEASUREMENT: Average drawing time for " << y_values_.size() << " elements: " << total_time.count() / 100 << " ns" << '\n';
        }
    }

    CloseWindow();
}

void BarPlot::exportAs(const std::string& filename) const {
    // Validate filename
    if (filename.empty()) {
        throw ChartasticError("Export filename cannot be empty");
    }
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".png") {
        throw ChartasticError("Export filename must end with .png extension");
    }

    // Validate we have data to export
    if (x_labels_.empty() || y_values_.empty()) {
        throw ChartasticError("Cannot export plot with no data");
    }

    // Set up hidden window for offscreen rendering
    SetConfigFlags(FLAG_WINDOW_HIDDEN);
    InitWindow(width_, height_, "Hidden");

    // Create render texture for offscreen rendering
    RenderTexture2D target = LoadRenderTexture(width_, height_);

    // Render to texture
    BeginTextureMode(target);
    renderChart();
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

} // namespace graphlib
