#include <chartastic/2d/function.hpp>
#include <raylib.h>
#include <algorithm>
#include <cmath>
#include <limits>

namespace chartastic {

void FunctionPlot::renderChart() const {
    const int left_padding = 80;
    const int right_padding = 80;
    const int top_padding = 80;
    const int bottom_padding = 80;

    ClearBackground(RAYWHITE);

    // Draw title
    DrawText(title_.c_str(), width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30, BLACK);

    int plot_left = left_padding;
    int plot_right = width_ - right_padding;
    int plot_bottom = height_ - bottom_padding;
    int plot_top = top_padding;

    int plot_width = plot_right - plot_left;
    int plot_height = plot_bottom - plot_top;

    // Calculate Y range if auto-scaling
    double y_min = y_min_;
    double y_max = y_max_;

    if (auto_scale_y_ && !functions_.empty()) {
        y_min = std::numeric_limits<double>::max();
        y_max = std::numeric_limits<double>::lowest();

        for (const auto& func_data : functions_) {
            for (int i = 0; i < num_points_; ++i) {
                double x = x_min_ + (x_max_ - x_min_) * i / (num_points_ - 1);
                double y = func_data.function->evaluate(x);
                if (std::isfinite(y)) {
                    y_min = std::min(y_min, y);
                    y_max = std::max(y_max, y);
                }
            }
        }

        // Add 10% padding
        double y_range = y_max - y_min;
        y_min -= y_range * 0.1;
        y_max += y_range * 0.1;
    }

    // Draw axes
    DrawLine(plot_left, plot_bottom, plot_right, plot_bottom, BLACK); // X-axis
    DrawLine(plot_left, plot_top, plot_left, plot_bottom, BLACK);     // Y-axis

    // Draw X-axis ticks and labels
    int num_x_ticks = 10;
    for (int i = 0; i <= num_x_ticks; ++i) {
        double x_val = x_min_ + (x_max_ - x_min_) * i / num_x_ticks;
        int x_px = plot_left + plot_width * i / num_x_ticks;

        DrawLine(x_px, plot_bottom, x_px, plot_bottom + 5, BLACK);

        char label[32];
        snprintf(label, sizeof(label), "%.1f", x_val);
        int text_width = MeasureText(label, 16);
        DrawText(label, x_px - text_width / 2, plot_bottom + 10, 16, DARKGRAY);
    }

    // Draw Y-axis ticks and labels
    int num_y_ticks = 8;
    for (int i = 0; i <= num_y_ticks; ++i) {
        double y_val = y_min + (y_max - y_min) * i / num_y_ticks;
        int y_px = plot_bottom - plot_height * i / num_y_ticks;

        DrawLine(plot_left - 5, y_px, plot_left, y_px, BLACK);

        char label[32];
        snprintf(label, sizeof(label), "%.1f", y_val);
        int text_width = MeasureText(label, 16);
        DrawText(label, plot_left - text_width - 10, y_px - 8, 16, DARKGRAY);
    }

    // Draw grid lines
    for (int i = 1; i < num_x_ticks; ++i) {
        int x_px = plot_left + plot_width * i / num_x_ticks;
        DrawLine(x_px, plot_top, x_px, plot_bottom, LIGHTGRAY);
    }
    for (int i = 1; i < num_y_ticks; ++i) {
        int y_px = plot_bottom - plot_height * i / num_y_ticks;
        DrawLine(plot_left, y_px, plot_right, y_px, LIGHTGRAY);
    }

    // Draw functions
    for (const auto& func_data : functions_) {
        std::vector<Vector2> points;
        points.reserve(num_points_);

        for (int i = 0; i < num_points_; ++i) {
            double x = x_min_ + (x_max_ - x_min_) * i / (num_points_ - 1);
            double y = func_data.function->evaluate(x);

            if (std::isfinite(y)) {
                // Map to screen coordinates
                int x_px = plot_left + static_cast<int>((x - x_min_) / (x_max_ - x_min_) * plot_width);
                int y_px = plot_bottom - static_cast<int>((y - y_min) / (y_max - y_min) * plot_height);

                points.push_back({static_cast<float>(x_px), static_cast<float>(y_px)});
            }
        }

        // Draw lines connecting points
        for (size_t i = 0; i + 1 < points.size(); ++i) {
            DrawLineV(points[i], points[i + 1], func_data.color);
        }
    }

    // Draw legend
    int legend_x = plot_right - 200;
    int legend_y = plot_top + 10;

    for (const auto& func_data : functions_) {
        DrawRectangle(legend_x, legend_y, 30, 3, func_data.color);
        DrawText(func_data.function->getLabel().c_str(), legend_x + 40, legend_y - 8, 18, BLACK);
        legend_y += 25;
    }
}

void FunctionPlot::show() const {
    if (functions_.empty()) {
        throw ChartasticError("Cannot show function plot with no functions added");
    }

    InitWindow(width_, height_, title_.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        renderChart();
        EndDrawing();
    }

    CloseWindow();
}

void FunctionPlot::exportAs(const std::string& filename) const {
    if (filename.empty()) {
        throw ChartasticError("Export filename cannot be empty");
    }
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".png") {
        throw ChartasticError("Export filename must end with .png extension");
    }

    if (functions_.empty()) {
        throw ChartasticError("Cannot export function plot with no functions added");
    }

    SetConfigFlags(FLAG_WINDOW_HIDDEN);
    InitWindow(width_, height_, "Hidden");

    RenderTexture2D target = LoadRenderTexture(width_, height_);

    BeginTextureMode(target);
    renderChart();
    EndTextureMode();

    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);

    if (!ExportImage(image, filename.c_str())) {
        UnloadImage(image);
        UnloadRenderTexture(target);
        CloseWindow();
        throw ChartasticError("Failed to export image to file: " + filename);
    }

    UnloadImage(image);
    UnloadRenderTexture(target);
    CloseWindow();
}

} // namespace chartastic
