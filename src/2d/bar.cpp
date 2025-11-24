#include <graphlib/2d/bar.hpp>
#include <raylib.h>
#include <algorithm>
#include <string>

namespace graphlib {

void BarPlot::show() const {
    const int width = 800;
    const int height = 600;
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);

    const int left_padding = 100;
    const int right_padding = 50;
    const int top_padding = 100;   // more space for title
    const int bottom_padding = 80;

    size_t n_bars = std::max<size_t>(1, x_labels.size());
    int plot_width = width - left_padding - right_padding;
    int bar_width = plot_width / static_cast<int>(n_bars);
    double max_y = *std::max_element(y_values.begin(), y_values.end());
    if (max_y == 0) max_y = 1;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int plot_bottom = height - bottom_padding;
        int plot_height = height - top_padding - bottom_padding;
        int plot_left = left_padding;

        // ----------------------
        // Draw title
        // ----------------------
        DrawText(title.c_str(), width/2 - MeasureText(title.c_str(), 30)/2, 20, 30, BLACK);

        // ----------------------
        // Draw y-axis
        // ----------------------
        DrawLine(plot_left, top_padding, plot_left, plot_bottom, BLACK);

        int n_div = 5;
        for (int i = 0; i <= n_div; ++i) {
            double y_val = max_y * i / n_div;
            int y_px = static_cast<int>(plot_bottom - (y_val / max_y) * plot_height);
            DrawLine(plot_left - 5, y_px, plot_left, y_px, BLACK);
            DrawText(std::to_string(static_cast<int>(y_val)).c_str(),
                     plot_left - 50, y_px - 10, 20, BLACK);
        }

        // ----------------------
        // Draw x-axis line
        // ----------------------
        DrawLine(plot_left, plot_bottom, width - right_padding, plot_bottom, BLACK);

        // ----------------------
        // Draw bars
        // ----------------------
        int total_bar_space = n_bars * bar_width;
        int start_x = plot_left + (plot_width - total_bar_space) / 2;

        for (size_t i = 0; i < n_bars; ++i) {
            double scaled_height = y_values[i] / max_y * plot_height;
            int x = start_x + static_cast<int>(i * bar_width);
            int y = static_cast<int>(plot_bottom - scaled_height);

            // Choose color: if user provided, use it; otherwise BLUE
            Color c = (i < colors.size()) ? colors[i] : BLUE;

            DrawRectangle(x, y, bar_width - 10, static_cast<int>(scaled_height), c);

            DrawText(x_labels[i].c_str(), x, height - bottom_padding + 5, 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
}

} // namespace graphlib

