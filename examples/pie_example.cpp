#include <chartastic/2d/pie.hpp>
#include <vector>

int main(){
    std::vector<int> grades = {81,82,82,83,83,83,84,84,84,84};
    chartastic::PiePlot plot(grades.begin(), grades.end());
    plot.setTitle("Exam Grade Pie Chart");
    plot.show();
}
