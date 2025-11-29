#include <graphlib/2d/pie.hpp>

namespace graphlib{

void PiePlot::show() const{
    int win_width = 800;
    int win_height = 600;
    InitWindow(win_width, win_height, title.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(title.c_str(), win_width / 2 - MeasureText(title.c_str(), 30) / 2, 20, 30, BLACK);

        int horiz_padding = 100; /* for one side */
        int vertical_padding = 100; /* for one side */

        int plot_width = win_width - 2 * horiz_padding;
        int plot_height = win_height - 2 * vertical_padding;

        int horiz_middle = horiz_padding + plot_width / 2;

        EndDrawing();
    }
    CloseWindow();
}

}
