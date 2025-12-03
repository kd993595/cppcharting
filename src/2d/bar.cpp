#include <chartastic/2d/bar.hpp>
#include <raylib.h>
#include <algorithm>
#include <string>
#include <sstream>

namespace chartastic {

void BarPlot::show() const {
    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(60);

    const int left_padding = 100;
    const int right_padding = 50;
    const int top_padding = 100;
    const int bottom_padding = 80;

    size_t n_bars = std::max<size_t>(1, x_labels_.size());
    double max_y = *std::max_element(y_values_.begin(), y_values_.end());
    if (max_y == 0) max_y = 1;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);

        if (orientation_ == Orientation::Vertical) {
            // (Vertical bars code stays the same)
        } else {
            // Horizontal bars
            int plot_height = height_ - top_padding - bottom_padding;
            int bar_height = plot_height / static_cast<int>(n_bars);
            int plot_left = left_padding;
            int plot_bottom = height_ - bottom_padding;
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

        EndDrawing();
    }

    CloseWindow();
}

} // namespace graphlib
