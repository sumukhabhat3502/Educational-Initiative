#include <iostream>
#include <map>
#include <set>
#include <vector>

class Point {
public:
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

class Grid {
public:
    int width, height;
    std::set<Point> obstacles;

    Grid(int width, int height) : width(width), height(height) {
        if (width < 0 || height < 0) {
            throw std::invalid_argument("Grid size must be positive.");
        }
    }

    void addObstacle(Point obstacle) {
        obstacles.insert(obstacle);
    }

    bool isObstacle(Point point) {
        return obstacles.count(point) > 0;
    }

    bool isWithinBounds(Point point) {
        return point.x >= 0 && point.x < width && point.y >= 0 && point.y < height;
    }
};

class Rover {
public:
    Point position;
    std::string direction;
    Grid& grid;

    Rover(int x, int y, std::string direction, Grid& grid) : position(x, y), direction(direction), grid(grid) {}

    void move() {
        Point nextPosition = position;
        if (direction == "N") nextPosition.y++;
        else if (direction == "S") nextPosition.y--;
        else if (direction == "E") nextPosition.x++;
        else if (direction == "W") nextPosition.x--;

        if (!grid.isObstacle(nextPosition)) {
            if (grid.isWithinBounds(nextPosition)) {
                position = nextPosition;
            } else {
                std::cout << "Error: Rover cannot move outside the grid.\n";
            }
        } else {
            throw std::runtime_error("Rover cannot move to an obstacle.");
        }
    }

    void turnLeft() {
        if (direction == "N") direction = "W";
        else if (direction == "S") direction = "E";
        else if (direction == "E") direction = "N";
        else if (direction == "W") direction = "S";
    }

    void turnRight() {
        if (direction == "N") direction = "E";
        else if (direction == "S") direction = "W";
        else if (direction == "E") direction = "S";
        else if (direction == "W") direction = "N";
    }

    void executeCommand(char command) {
        if (command == 'M') move();
        else if (command == 'L') turnLeft();
        else if (command == 'R') turnRight();
    }

    void printStatus() {
        std::cout << "Rover Status:\n";
        std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
        std::cout << "Direction: " << direction << "\n";
    }
};

int main() {
    int x, y;
    std::string direction;
    std::cout << "Enter the starting position of the rover (x, y, direction):\n";
    std::cin >> x >> y >> direction;

    int width, height;
    std::cout << "Enter the size of the grid (width, height):\n";
    std::cin >> width >> height;

    Grid grid(width, height);

    int numObstacles;
    std::cout << "Enter the number of obstacles:\n";
    std::cin >> numObstacles;

    for (int i = 0; i < numObstacles; i++) {
        std::cout << "Enter the coordinates of obstacle " << (i + 1) << " (x, y):\n";
        std::cin >> x >> y;
        grid.addObstacle(Point(x, y));
    }

    Rover rover(x, y, direction, grid);

    std::cout << "Enter the commands for the rover:\n";
    std::string commands;
    std::cin >> commands;

    for (char command : commands) {
        rover.executeCommand(command);
    }

    rover.printStatus();

    return 0;
}