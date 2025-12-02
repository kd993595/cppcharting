#include <graphlib/2d/pie.hpp>
#include <vector>

int main(){
    std::vector<int> grades = {81,82,82,83,83,83,84,84,84,84};
    auto plot = graphlib::pie(grades.begin(), grades.end());
    plot.title = "Exam Grade Pie Chart";
    plot.color = RED;
    plot.show();
}
