#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

class Rover {
public:
    Point position;
    char direction;
    map<char, void (Rover::*)()> commands;

    Rover(int x, int y, char direction) : position{x, y}, direction{direction} {
        commands['M'] = &Rover::move;
        commands['L'] = &Rover::turnLeft;
        commands['R'] = &Rover::turnRight;
    }

    void move() {
        if (direction == 'N') position.y++;
        else if (direction == 'S') position.y--;
        else if (direction == 'E') position.x++;
        else if (direction == 'W') position.x--;
    }

    void turnLeft() {
        if (direction == 'N') direction = 'W';
        else if (direction == 'S') direction = 'E';
        else if (direction == 'E') direction = 'N';
        else if (direction == 'W') direction = 'S';
    }

    void turnRight() {
        if (direction == 'N') direction = 'E';
        else if (direction == 'S') direction = 'W';
        else if (direction == 'E') direction = 'S';
        else if (direction == 'W') direction = 'N';
    }

    void executeCommand(char command) {
        (this->*commands[command])();
    }
};

class Grid {
public:
    int width, height;
    set<Point> obstacles;

    Grid(int width, int height) : width{width}, height{height} {}

    void addObstacle(Point obstacle) {
        obstacles.insert(obstacle);
    }

    bool isObstacle(Point point) {
        return obstacles.count(point);
    }
};

int main() {
    int x, y;
    char direction;
    cout << "Enter the starting position of the rover (x, y, direction): ";
    cin >> x >> y >> direction;

    Rover rover(x, y, direction);

    int width, height;
    cout << "Enter the size of the grid (width, height): ";
    cin >> width >> height;

    Grid grid(width, height);

    int numObstacles;
    cout << "Enter the number of obstacles: ";
    cin >> numObstacles;

    for (int i = 0; i < numObstacles; i++) {
        cout << "Enter the coordinates of obstacle " << i + 1 << " (x, y): ";
        cin >> x >> y;
        grid.addObstacle({x, y});
    }

    cout << "Enter the commands for the rover: ";
    string commands;
    cin >> commands;

    for (char command : commands) {
        Point nextPoint = rover.position;
        if (command == 'M') {
            if (rover.direction == 'N') nextPoint.y++;
            else if (rover.direction == 'S') nextPoint.y--;
            else if (rover.direction == 'E') nextPoint.x++;
            else if (rover.direction == 'W') nextPoint.x--;
        }

        if (!grid.isObstacle(nextPoint)) {
            rover.executeCommand(command);
        }
    }

    cout << "Final Position: (" << rover.position.x << ", " << rover.position.y << ", " << rover.direction << ")\n";

    return 0;
}