#include <iostream>
#include <random>
#include <vector>

// Structure to represent a point in 2D
struct Point {
    double x;
    double y;
};

// Function to generate n random points in a box centered around the origin
std::vector<Point> generateRandomPoints(int n, double boxWidth, double boxHeight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(-boxWidth/2, boxWidth/2);
    std::uniform_real_distribution<> disY(-boxHeight/2, boxHeight/2);

    std::vector<Point> points;
    points.reserve(n);
    for (int i = 0; i < n; ++i) {
        Point p;
        p.x = disX(gen);
        p.y = disY(gen);
        points.push_back(p);
    }
    return points;
}

int main() {
    int n = 10; // Number of points
    double boxWidth = 10.0; // Width of the box
    double boxHeight = 10.0; // Height of the box

    std::vector<Point> randomPoints = generateRandomPoints(n, boxWidth, boxHeight);

    // Print out the generated points
    for (const auto& point : randomPoints) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }

    return 0;
}
