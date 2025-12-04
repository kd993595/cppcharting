#include <cmath>
#include <chartastic/2d/pie.hpp>
#include <map>
#include <numbers>

namespace chartastic{

void PiePlot::renderChart() const{
    std::map<double, int> counts;

    for (auto& value : values){
        counts[value]++;
    }

    DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);

    int horiz_padding = 100; /* for one side */
    int vertical_padding = 100; /* for one side */

    int plot_width = width_ - 2 * horiz_padding;
    int plot_height = height_ - 2 * vertical_padding;

    /* float type required for Vector2 */
    float horiz_middle = horiz_padding + plot_width / 2;
    float vert_middle = vertical_padding + plot_height / 2;
    Vector2 center = {horiz_middle, vert_middle};

    int radius = 150;
    double angle_start = 0;
    double angle_end = 0;

    int x_legend = width_ - 125;
    int y_legend = 50;
    int legend_box = 20;
    int legend_gap = 10;

    int color_index = 0; /* will wrap around */
    int slice_index = 0; /* will not wrap around */

    for (auto& [key, value] : counts){
        double count_portion = counts[key] / static_cast<double>(values.size());
        double angle_portion = count_portion * 360;

        angle_end += angle_portion;

        /* create the slice */
        DrawCircleSector(center, radius, angle_start, angle_end, 100, palette[color_index]);

        double angle_mid = (angle_start + angle_end) / 2;
        double radians_mid = angle_mid * (std::numbers::pi / 180);

        /* some trigonometry to find (x,y) relative to (0,0) here */
        double x_offset = std::cos(radians_mid) * radius;
        double y_offset = std::sin(radians_mid) * radius;

        /* scale offsets to have them be closer to slice's middle */
        x_offset *= 0.65;
        y_offset *= 0.65;

        double x_text = horiz_middle + x_offset;
        double y_text = vert_middle + y_offset;

        /* label inside the slice */
        const char* pie_label = TextFormat("%g%%", count_portion * 100);
        int text_width = MeasureText(pie_label, 22);
        DrawText(pie_label, x_text - text_width / 2, y_text - 6, 22, BLACK);

        /* legend entry */
        DrawRectangle(x_legend, y_legend + slice_index * (legend_box + legend_gap), legend_box, legend_box, palette[color_index]);
        DrawText(TextFormat("%g", key), x_legend + legend_box + 10, y_legend + slice_index * (legend_box + legend_gap), 22, BLACK);

        color_index++;
        slice_index++;

        color_index = color_index % palette.size();

        angle_start = angle_end;
    }
}

void PiePlot::show() const{
    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        renderChart();
        EndDrawing();
    }

    CloseWindow();
}

}
