#include <algorithm>
#include <chartastic/2d/area.hpp>
#include <raylib.h>
#include <string>

namespace chartastic {

void AreaPlot::show() const {
	InitWindow(width_, height_, title_.c_str());
	SetTargetFPS(60);

	const int left_padding = 100;
	const int bottom_padding = 80;
	const int top_padding = 80;
	const int right_padding = 50;

	size_t n = x_labels_.size();
	double max_y = *std::max_element(y_values_.begin(), y_values_.end());
	if (max_y == 0)
		max_y = 1;

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(RAYWHITE);

		int plot_left = left_padding;
		int plot_right = width_ - right_padding;
		int plot_bottom = height_ - bottom_padding;
		int plot_top = top_padding;

		int plot_width = plot_right - plot_left;
		int plot_height = plot_bottom - plot_top;

		// Title
		DrawText(title_.c_str(),
				 width_ / 2 - MeasureText(title_.c_str(), 30) / 2, 20, 30,
				 BLACK);

		// Compute points
		std::vector<Vector2> pts;
		pts.reserve(n);

		for (size_t i = 0; i < n; i++) {
			double norm_y = y_values_[i] / max_y;
			int x = plot_left + (int)((i / (double)(n - 1)) * plot_width);
			int y = plot_bottom - (int)(norm_y * plot_height);
			pts.push_back(Vector2{(float)x, (float)y});
		}

		// Draw AREA FILL first
		for (size_t i = 0; i + 1 < pts.size(); i++) {
			DrawTriangle(Vector2{pts[i].x, (float)plot_bottom},
						 Vector2{pts[i + 1].x, (float)plot_bottom}, pts[i],
						 fill_color_);
			DrawTriangle(pts[i], Vector2{pts[i + 1].x, (float)plot_bottom},
						 pts[i + 1], fill_color_);
		}

		// Draw LINE on top of the area
		for (size_t i = 0; i + 1 < pts.size(); i++) {
			DrawLineV(pts[i], pts[i + 1], DARKBLUE);
		}

		// Y-axis ticks
		for (int i = 0; i <= 5; i++) {
			double y_val = max_y * i / 5;
			int y_px = plot_bottom - (y_val / max_y) * plot_height;

			DrawLine(plot_left - 5, y_px, plot_left, y_px, BLACK);
			DrawText(std::to_string((int)y_val).c_str(), plot_left - 50,
					 y_px - 10, 20, BLACK);
		}

		// X-axis
		DrawLine(plot_left, plot_bottom, plot_right, plot_bottom, BLACK);

		// Y-axis
		DrawLine(plot_left, plot_top, plot_left, plot_bottom, BLACK);
		// Draw X-axis text
		for (size_t i = 0; i < n; i++) {
			int label_x = pts[i].x - MeasureText(x_labels_[i].c_str(), 20) / 2;
			int label_y = plot_bottom + 5;
			DrawText(x_labels_[i].c_str(), label_x, label_y, 20, BLACK);
		}
		EndDrawing();
	}

	CloseWindow();
}

} // namespace chartastic
