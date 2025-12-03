#include <algorithm>
#include <chartastic/3d/bar.hpp>
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <sstream>
#include <string>

namespace chartastic {

void BarPlot3D::show() const {
	InitWindow(width_, height_, title_.c_str());
	SetTargetFPS(60);

	// Camera setup
	Camera3D camera = {0};
	camera.position = (Vector3){10.0f, 10.0f, 10.0f};
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	// Mouse control variables
	Vector2 lastMousePos = GetMousePosition();
	float cameraAngleX = camera_angle_x_;
	float cameraAngleY = camera_angle_y_;
	float cameraDistance = camera_distance_;

	// Find max value for scaling
	size_t n_bars = std::max<size_t>(1, x_labels_.size());
	double max_y = *std::max_element(y_values_.begin(), y_values_.end());
	if (max_y == 0)
		max_y = 1;

	// Scaling factor for bar heights
	const float max_height = 5.0f;

	while (!WindowShouldClose()) {
		// Handle mouse input for camera control
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 currentMousePos = GetMousePosition();
			Vector2 mouseDelta = {currentMousePos.x - lastMousePos.x,
								  currentMousePos.y - lastMousePos.y};

			// Update camera angles based on mouse movement
			cameraAngleY += mouseDelta.x * 0.3f;
			cameraAngleX += mouseDelta.y * 0.3f;

			if (cameraAngleX > 89.0f)
				cameraAngleX = 89.0f;
			if (cameraAngleX < -89.0f)
				cameraAngleX = -89.0f;

			lastMousePos = currentMousePos;
		} else {
			lastMousePos = GetMousePosition();
		}

		// Handle mouse wheel for zoom
		float wheel = GetMouseWheelMove();
		cameraDistance -= wheel * 0.5f;
		if (cameraDistance < 5.0f)
			cameraDistance = 5.0f;
		if (cameraDistance > 30.0f)
			cameraDistance = 30.0f;

		// Update camera position based on angles and distance
		float angleXRad = cameraAngleX * DEG2RAD;
		float angleYRad = cameraAngleY * DEG2RAD;

		camera.position.x = cameraDistance * cosf(angleXRad) * cosf(angleYRad);
		camera.position.y = cameraDistance * sinf(angleXRad);
		camera.position.z = cameraDistance * cosf(angleXRad) * sinf(angleYRad);

		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		// Draw grid on the floor
		DrawGrid(20, 1.0f);

		// Calculate bar spacing
		float bar_width = 0.6f;
		float bar_spacing = 1.2f;
		float total_width = n_bars * bar_spacing;
		float start_x = -total_width / 2.0f + bar_spacing / 2.0f;

		// Draw 3D bars
		for (size_t i = 0; i < n_bars; ++i) {
			float bar_height =
				static_cast<float>(y_values_[i] / max_y * max_height);
			float x_pos = start_x + i * bar_spacing;

			Color bar_color = (i < colors_.size()) ? colors_[i] : BLUE;

			// Draw the bar as a cube
			DrawCube((Vector3){x_pos, bar_height / 2.0f, 0.0f}, bar_width,
					 bar_height, bar_width, bar_color);

			// Draw bar outline
			DrawCubeWires((Vector3){x_pos, bar_height / 2.0f, 0.0f}, bar_width,
						  bar_height, bar_width, BLACK);
		}

		// Draw axes
		DrawLine3D((Vector3){-total_width / 2 - 1, 0, 0},
				   (Vector3){total_width / 2 + 1, 0, 0}, RED); // X-axis
		DrawLine3D((Vector3){0, 0, 0}, (Vector3){0, max_height + 1, 0},
				   GREEN);										   // Y-axis
		DrawLine3D((Vector3){0, 0, -5}, (Vector3){0, 0, 5}, BLUE); // Z-axis

		EndMode3D();

		// Draw 2D UI overlay
		DrawText(title_.c_str(), 10, 10, 30, BLACK);

		// Draw labels
		int label_y = 50;
		for (size_t i = 0; i < n_bars; ++i) {
			std::stringstream ss;
			ss << x_labels_[i] << ": " << y_values_[i];
			Color label_color = (i < colors_.size()) ? colors_[i] : BLUE;
			DrawRectangle(10, label_y, 20, 20, label_color);
			DrawText(ss.str().c_str(), 35, label_y, 20, BLACK);
			label_y += 25;
		}

		EndDrawing();
	}

	CloseWindow();
}

} // namespace chartastic
