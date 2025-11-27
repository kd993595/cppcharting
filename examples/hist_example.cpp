#include <graphlib/2d/hist.hpp>
#include <vector>

int main(){
    std::vector<int> grades = {83,91,93,84,99,89,60,94,97,92,93,85,97,66,59,88,80,81,96,83,99,65,59,98,82,81,94,68,72,77,82};
    auto plot = graphlib::hist(grades.begin(), grades.end(), 5);
    plot.title = "Exam Grade Histogram";
    plot.color = RED;
    plot.show();
}
