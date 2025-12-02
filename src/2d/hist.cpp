#include <algorithm>
#include <cmath>
#include <chartastic/2d/hist.hpp>

namespace chartastic {

void HistPlot::show() const{
    int win_width = 800;
    int win_height = 600;
    InitWindow(win_width, win_height, title.c_str());
    SetTargetFPS(60);

    auto it_min_val = std::min_element(values.begin(), values.end());
    double min_val = *it_min_val;

    auto it_max_val = std::max_element(values.begin(), values.end());
    double max_val = *it_max_val;

    double min_max_range = max_val - min_val;
    double bin_width = min_max_range / bin_count;

    /* need to give bin some width when min_val == max_val */
    bin_width = min_val == max_val ? 1 : bin_width;

    std::vector<int> bins(bin_count, 0);

    for (auto& value : values){
        int bin_index = std::floor((value - min_val) / bin_width);

        /* to prevent index out of bounds for when value == max_val */
        bin_index = value == max_val ? bin_count - 1 : bin_index;
        bins[bin_index] += 1;
    }

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(title.c_str(), win_width / 2 - MeasureText(title.c_str(), 30) / 2, 20, 30, BLACK);

        int horiz_padding = 50; /* for one side */
        int vertical_padding = 50; /* for one side */

        int plot_width = win_width - 2 * horiz_padding;
        int plot_height = win_height - 2 * vertical_padding;
        int bin_size = plot_width / bin_count;

        /* y-axis */
        DrawLine(horiz_padding, win_height - vertical_padding, horiz_padding, vertical_padding, BLACK);

        /* x-axis */
        DrawLine(horiz_padding, win_height - vertical_padding, win_width - horiz_padding, win_height - vertical_padding, BLACK);

        auto it_max_bin_count = std::max_element(bins.begin(), bins.end());
        int max_bin_count = *it_max_bin_count;

        for (int i = 0; i < bin_count; ++i){
            /* pixels are only integers; round up to ensure visibility for even small heights */
            /* scaled relative to max bin */
            int bin_height = std::round((bins[i] / static_cast<double>(max_bin_count)) * plot_height);

            int bin_x = horiz_padding + i * bin_size;
            int bin_y = win_height - vertical_padding - bin_height;

            /* draw the bin */
            DrawRectangle(bin_x, bin_y, bin_size, bin_height, color);
        }

        /* y-axis ticks */
        int y_tick_segments = max_bin_count < 6 ? max_bin_count : 6; /* tick count is +1 of this */
        for (int i = 0; i < y_tick_segments + 1; ++i){
            double portion = i / static_cast<double>(y_tick_segments);
            int tick_y = (win_height - vertical_padding) - portion * plot_height;
            int tick_val = portion * max_bin_count;

            DrawLine(horiz_padding - 10, tick_y, horiz_padding, tick_y, BLACK);
            DrawText(std::to_string(tick_val).c_str(), horiz_padding - 35, tick_y - 6, 16, BLACK);
        }

        /* x-axis ticks */
        int x_tick_segments = bin_count; /* tick count is +1 of this */
        for (int i = 0; i < x_tick_segments + 1; ++i){
            double portion = i / static_cast<double>(x_tick_segments);
            int tick_x = horiz_padding + i * bin_size;
            double tick_val = min_val + i * bin_width;

            DrawLine(tick_x, win_height - vertical_padding, tick_x, win_height - vertical_padding + 10, BLACK);

            /* see if the tick_val stores an integer or an actual decimal */
            if (tick_val == std::floor(tick_val)){
                DrawText(std::to_string(static_cast<int>(tick_val)).c_str(), tick_x - 3, win_height - vertical_padding + 20, 16, BLACK);
            }
            else{
                DrawText(TextFormat("%.1f", tick_val), tick_x - 8, win_height - vertical_padding + 20, 16, BLACK);
            }
        }
        EndDrawing();
    }
    CloseWindow();
}

}
