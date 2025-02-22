package csci.ooad.polymorphia.stepdefs

import csci.ooad.Entities.Adventurer
import csci.ooad.Entities.Creature
import csci.ooad.Maze
import csci.ooad.Polymorphia
import io.cucumber.java.en.Given
import io.cucumber.java.en.Then
import io.cucumber.java.en.When

class MazeStepDefs {
    World world;

    MazeStepDefs(World world) {
        this.world = world;
    }

    @Given("I have a maze with {int}x{int} rooms")
    public void mazeWithNxMRooms(int rows, int cols) {
        this.world.maze = Maze.Builder.getNewBuilder()
                .addFoodByNumber(20)
                .addDemonsByNumber(10)
                .addCowardsByNumber(10)
                .addAdventurersByNumber(10)
                .addKnightsByNumber(10)
                .addGluttonsByNumber(10)
                .addCreaturesByNumber(10)
                .createNxMGridConnectedRooms(rows, cols).build();
    }
    @Then("There are {int} times {int} room names")
    public void checkForNxMRoomNames(int rows, int cols) {
        assert(this.world.maze.getRooms().size() == rows * cols);
    }
}
