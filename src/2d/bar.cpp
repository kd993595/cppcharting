#include <graphlib/2d/bar.hpp>
#include <raylib.h>
#include <algorithm>
#include <string>

namespace graphlib {

void BarPlot::show() const {
    const int width = 800;
    const int height = 600;
    InitWindow(width, height, "Bar Plot Example");
    SetTargetFPS(60);

    // Padding around plot
    const int left_padding = 100;
    const int right_padding = 50;
    const int top_padding = 50;
    const int bottom_padding = 80;

    // Number of bars
    size_t n_bars = std::max<size_t>(1, x_labels.size());

    // Compute bar width
    int plot_width = width - left_padding - right_padding;
    int bar_width = plot_width / static_cast<int>(n_bars);

    // Find max y for scaling
    double max_y = *std::max_element(y_values.begin(), y_values.end());
    if (max_y == 0) max_y = 1; // avoid division by zero

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ----------------------
        // Draw y-axis
        // ----------------------
        DrawLine(left_padding, top_padding, left_padding, height - bottom_padding, BLACK);

        // Draw y-axis labels (5 divisions)
        int n_div = 5;
        for (int i = 0; i <= n_div; ++i) {
            double y_val = max_y * i / n_div;
            int y_px = static_cast<int>(height - bottom_padding - (y_val / max_y) * (height - top_padding - bottom_padding));
            DrawLine(left_padding - 5, y_px, left_padding, y_px, BLACK);
            DrawText(std::to_string(static_cast<int>(y_val)).c_str(),
                     left_padding - 50, y_px - 10, 20, BLACK);
        }

        // ----------------------
        // Draw bars
        // ----------------------
        int plot_left = left_padding;
        int plot_bottom = height - bottom_padding;
        int plot_height = height - top_padding - bottom_padding;

        // Compute total width of all bars including spacing
        int total_bar_space = n_bars * bar_width;
        int start_x = plot_left + (plot_width - total_bar_space) / 2; // center bars

        for (size_t i = 0; i < n_bars; ++i) {
            double scaled_height = y_values[i] / max_y * plot_height;
            int x = start_x + static_cast<int>(i * bar_width);
            int y = static_cast<int>(plot_bottom - scaled_height);

            DrawRectangle(x, y, bar_width - 10, static_cast<int>(scaled_height), BLUE);

            // Draw labels
            DrawText(x_labels[i].c_str(), x, height - bottom_padding + 5, 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
}

} // namespace graphlib
