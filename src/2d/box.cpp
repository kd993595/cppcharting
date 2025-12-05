#include <algorithm>
#include <cmath>
#include <chartastic/2d/box.hpp>
#include <chrono>
#include <iostream>

namespace chartastic {

/* assumes that vec is already sorted */
double get_percentile(const std::vector<double>& vec, double q){
    int n = vec.size();
    int j = q * (n - 1); /* integral part */
    double g = (q * (n - 1)) - j; /* fractional part */
    return (1 - g) * vec[j] + g * vec[j + 1];
}

void BoxPlot::renderChart() const{
    std::vector<double> vec = values;
    std::sort(vec.begin(), vec.end());

    double min = vec.front();
    double q1 = get_percentile(vec, 0.25);
    double q2 = get_percentile(vec, 0.50);
    double q3 = get_percentile(vec, 0.75);
    double max = vec.back();
    double range = max - min;

    DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);

    int horiz_padding = 100; /* for one side */
    int vertical_padding = 100; /* for one side */

    int plot_width = width_ - 2 * horiz_padding;
    int plot_height = height_ - 2 * vertical_padding;

    int horiz_middle = horiz_padding + plot_width / 2;

    /* y-axis */
    DrawLine(horiz_padding, height_ - vertical_padding, horiz_padding, vertical_padding, BLACK);

    /* draw the min */
    DrawLine(horiz_middle - 25, height_ - vertical_padding, horiz_middle + 25, height_ - vertical_padding, color);

    /* draw the box */
    double q1_portion = (q1 - min) / range;
    int q1_y_offset = q1_portion * plot_height;
    int q1_y = height_ - vertical_padding - q1_y_offset;

    double q3_portion = (q3 - min) / range;
    int q3_y_offset = q3_portion * plot_height;
    int q3_y = height_ - vertical_padding - q3_y_offset;

    /* for vertical boxplot q1 has larger y value than q3 */
    int box_width = 80;
    int iqr_size = q1_y - q3_y;

    DrawRectangleLines(horiz_middle - box_width / 2, q3_y, box_width, iqr_size, color);

    /* draw the median */
    double q2_portion = (q2 - min) / range;
    int q2_y_offset = q2_portion * plot_height;
    int q2_y = height_ - vertical_padding - q2_y_offset;

    DrawLine(horiz_middle - box_width / 2, q2_y, horiz_middle + box_width / 2, q2_y, color);

    /* draw the max */
    DrawLine(horiz_middle - 25, vertical_padding, horiz_middle + 25, vertical_padding, color);

    /* connect the min and max to the box */
    DrawLine(horiz_middle, height_ - vertical_padding, horiz_middle, q1_y, color);
    DrawLine(horiz_middle, vertical_padding, horiz_middle, q3_y, color);

    /* y-axis ticks */
    int y_tick_segments = 6; /* tick count is +1 of this */
    for (int i = 0; i < y_tick_segments + 1; ++i){
        double portion = i / static_cast<double>(y_tick_segments);
        int tick_y = (height_ - vertical_padding) - portion * plot_height;
        double tick_val = min + portion * range;

        DrawLine(horiz_padding - 10, tick_y, horiz_padding, tick_y, BLACK);

        /* see if the tick_val stores an integer or an actual decimal */
        if (tick_val == std::floor(tick_val)){
            DrawText(std::to_string(static_cast<int>(tick_val)).c_str(), horiz_padding - 45, tick_y - 6, 16, BLACK);
        }
        else{
            DrawText(TextFormat("%.1f", tick_val), horiz_padding - 50, tick_y - 6, 16, BLACK);
        }
    }
}

void BoxPlot::show() const{
    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(60);

    std::chrono::nanoseconds total_time {0};
    int frames = 0;

    while (!WindowShouldClose()){
        auto t_start = std::chrono::system_clock::now();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        renderChart();
        EndDrawing();

        auto t_end = std::chrono::system_clock::now();

        total_time += std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
        frames++;

        if (frames == 100){
            std::cout << "MEASUREMENT: Average drawing time for " << values.size() << " elements: " << total_time.count() / 100 << " ns" << '\n';
        }
    }

    CloseWindow();
}

}
