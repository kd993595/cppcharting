#include <algorithm>
#include <cmath>
#include <graphlib/2d/hist.hpp>

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
    int bin_count = std::ceil(min_max_range / bin_width);

    /* need to give one bin when min_val == max_val */
    bin_count = min_val == max_val ? 1 : bin_count;
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

        int horiz_padding = 50; /* for one side */
        int vertical_padding = 50; /* for one side */

        int plot_width = win_width - 2 * horiz_padding;
        int plot_height = win_height - 2 * vertical_padding;
        int bin_size = plot_width / bin_count;

        /* y-axis */
        DrawLine(horiz_padding, win_height - vertical_padding, horiz_padding, vertical_padding, BLACK);

        /* x-axis */
        DrawLine(horiz_padding, win_height - vertical_padding, win_width - horiz_padding, win_height - vertical_padding, BLACK);

        for (int i = 0; i < bin_count; ++i){
            auto it_max_bin_count = std::max_element(bins.begin(), bins.end());
            int max_bin_count = *it_max_bin_count;

            /* pixels are only integers; round up to ensure visibility for even small heights */
            /* scaled relative to max bin */
            int bin_height = std::round((bins[i] / static_cast<double>(max_bin_count)) * plot_height);

            int bin_x = horiz_padding + i * bin_size;
            int bin_y = win_height - vertical_padding - bin_height;

            /* draw the bin */
            DrawRectangle(bin_x, bin_y, bin_size, bin_height, color);
        }
        EndDrawing();
    }
    CloseWindow();
}
