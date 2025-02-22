package csci.ooad;

import org.junit.jupiter.api.Test;

public class MazeTest {
    private final int NUM_SEQUENTIAL_ROOMS = 4;
    @Test
    public void TestMaze() {
        Maze sequentialMaze = Maze.Builder.getNewBuilder()
                .addAdventurersByNumber(NUM_SEQUENTIAL_ROOMS)
                .addFoodByNumber(NUM_SEQUENTIAL_ROOMS)
                .addCreaturesByNumber(NUM_SEQUENTIAL_ROOMS)
                .createNFullyConnectedRooms(NUM_SEQUENTIAL_ROOMS)
                .distributeSequentially()
                .build();
        /*for (Room room : sequentialMaze.getRooms()) {
            assert(room.getNumOfNeighboringRooms() == (NUM_SEQUENTIAL_ROOMS-1));
            assert(room.hasCreatures());
            assert(room.hasFoods());
            assert(room.hasAdventurers());
        }*/
    }
}
