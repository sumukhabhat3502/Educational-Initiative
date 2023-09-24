import java.util.*;

interface Command {
    void execute();
}

class Rover {
    int x, y;
    String direction;
    Map<String, Command> commands = new HashMap<>();

    Rover(int x, int y, String direction) {
        this.x = x;
        this.y = y;
        this.direction = direction;
        commands.put("M", this::move);
        commands.put("L", this::turnLeft);
        commands.put("R", this::turnRight);
    }

    void move() {
        if (direction.equals("N"))
            y++;
        else if (direction.equals("S"))
            y--;
        else if (direction.equals("E"))
            x++;
        else if (direction.equals("W"))
            x--;
    }

    void turnLeft() {
        if (direction.equals("N"))
            direction = "W";
        else if (direction.equals("S"))
            direction = "E";
        else if (direction.equals("E"))
            direction = "N";
        else if (direction.equals("W"))
            direction = "S";
    }

    void turnRight() {
        if (direction.equals("N"))
            direction = "E";
        else if (direction.equals("S"))
            direction = "W";
        else if (direction.equals("E"))
            direction = "S";
        else if (direction.equals("W"))
            direction = "N";
    }

    void executeCommand(String command) {
        commands.get(command).execute();
    }
}

class Grid {
    int width, height;
    Set<Point> obstacles = new HashSet<>();

    Grid(int width, int height) {
        this.width = width;
        this.height = height;
    }

    void addObstacle(Point obstacle) {
        obstacles.add(obstacle);
    }

    boolean isObstacle(Point point) {
        return obstacles.contains(point);
    }
}

class Point {
    int x, y;

    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;
        Point point = (Point) o;
        return x == point.x && y == point.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}

public class rover {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the starting position of the rover (x, y, direction):");
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        String direction = scanner.next();

        Rover rover = new Rover(x, y, direction);

        System.out.println("Enter the size of the grid (width, height):");
        int width = scanner.nextInt();
        int height = scanner.nextInt();

        Grid grid = new Grid(width, height);

        System.out.println("Enter the number of obstacles:");
        int numObstacles = scanner.nextInt();

        for (int i = 0; i < numObstacles; i++) {
            System.out.println("Enter the coordinates of obstacle " + (i + 1) + " (x, y):");
            int obstacleX = scanner.nextInt();
            int obstacleY = scanner.nextInt();
            grid.addObstacle(new Point(obstacleX, obstacleY));
        }

        System.out.println("Enter the commands for the rover:");
        String[] commands = scanner.next().split("");

        for (String command : commands) {
            Point nextPoint = new Point(rover.x, rover.y);
            if (command.equals("M")) {
                if (rover.direction.equals("N"))
                    nextPoint.y++;
                else if (rover.direction.equals("S"))
                    nextPoint.y--;
                else if (rover.direction.equals("E"))
                    nextPoint.x++;
                else if (rover.direction.equals("W"))
                    nextPoint.x--;
            }

            if (!grid.isObstacle(nextPoint)) {
                rover.executeCommand(command);
            }
        }

        System.out.println("Final Position: (" + rover.x + ", " + rover.y + ", " + rover.direction + ")");
    }
}