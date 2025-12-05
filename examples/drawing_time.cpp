#include <chartastic/2d/area.hpp>
#include <chartastic/2d/bar.hpp>
#include <chartastic/2d/box.hpp>
#include <chartastic/2d/hist.hpp>
#include <chartastic/2d/line.hpp>
#include <chartastic/2d/pie.hpp>
#include <chartastic/2d/scatter.hpp>
#include <iostream>
#include <random>
#include <vector>

int main(){
    std::vector<int> counts {10, 100, 1'000};
    std::vector<int> seeds {30, 60, 90};

    for (auto& count : counts){
        for (auto& seed : seeds){
            std::default_random_engine random_engine {};
            random_engine.seed(seed);
            std::uniform_int_distribution number_dist {1, 100}; // inclusive range

            std::vector<int> numbers;
            std::vector<std::string> strings; // give it some arbitrary strings
            std::vector<int> indices;
            for (int i = 0; i < count; ++i){
                auto next = number_dist(random_engine);
                numbers.push_back(next);
                strings.push_back(std::to_string(next));
                indices.push_back(i);
            }

            /* area chart */
            chartastic::AreaPlot area_plot(strings.begin(), strings.end(), numbers.begin(), numbers.end());
            area_plot.setTitle("Fruit Sales Area");
            area_plot.setFillColor(SKYBLUE);
            area_plot.show();

            /* bar chart */
            chartastic::BarPlot bar_plot(strings.begin(), strings.end(), numbers.begin(), numbers.end());
            bar_plot.setTitle("Fruit Sales");
            bar_plot.setColors({RED, YELLOW, GREEN, ORANGE});
            bar_plot.setOrientation(chartastic::Orientation::Horizontal);
            bar_plot.show();

            /* box chart */
            chartastic::BoxPlot box_plot(numbers.begin(), numbers.end());
            box_plot.setTitle("Exam Grade Boxplot");
            box_plot.setColor(RED);
            box_plot.show();

            /* histogram */
            chartastic::HistPlot hist_plot(numbers.begin(), numbers.end(), 5);
            hist_plot.setTitle("Exam Grade Histogram");
            hist_plot.setColor(RED);
            hist_plot.show();

            /* line plot */
            chartastic::Line line_plot("My Line Plot", 1, 100, 1, 100, "x axis name", "y axis name", true);
            line_plot.setColors(chartastic::ColorPalette::palette2);
            line_plot.addLine(indices.begin(), indices.end(), numbers.begin(), numbers.end());
            line_plot.show();

            /* pie chart */
            chartastic::PiePlot pie_plot(numbers.begin(), numbers.end());
            pie_plot.setTitle("Exam Grade Pie Chart");
            pie_plot.setPalette({RED, BLUE, GREEN, ORANGE});
            pie_plot.show();

            /* scatter plot */
            chartastic::Scatter scatter_plot("My Scatter Plot", 1, 100, 1, 100, "My x axis(cm)", "Y axis name(4)",true);
            scatter_plot.addScatter(numbers.begin(), numbers.end(), numbers.begin(), numbers.end());
            scatter_plot.show();
        }
    }
}
