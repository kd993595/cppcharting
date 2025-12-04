#include <chartastic/3d/pie.hpp>
#include <raylib.h>
#include <vector>

int main(){
    std::vector<int> grades = {81,82,82,83,83,83,84,84,84,84};
    chartastic::PiePlot3D plot(grades.begin(), grades.end());
    plot.setTitle("Exam Grade Pie Chart");
    plot.setPalette({RED, BLUE, GREEN, ORANGE});
    plot.show();
}
