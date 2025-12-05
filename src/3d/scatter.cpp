#include <chartastic/3d/scatter.hpp>
#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <sstream>
#include <string>

namespace chartastic {

void ScatterPlot3D::show() const {
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

	// Scaling factor for bar heights
	const float max_height = 5.0f;
	const float total_width = 10.0f;

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

		// Draw points
		for(size_t i=0;i<x_values_.size();++i){
      for(size_t j=0;j<x_values_[i].size();++j){
        DrawSphere((Vector3){x_values_[i][j], y_values_[i][j], z_values_[i][j]}, .5f, colors_[i]);
      }
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
		for (size_t i = 0; i < labels_.size(); ++i) {
			DrawRectangle(10, label_y, 20, 20, colors_[i]);
			DrawText(labels_[i].c_str(), 35, label_y, 20, BLACK);
			label_y += 25;
		}

		EndDrawing();
	}

	CloseWindow();
}

} // namespace chartastic
