package csci.ooad.polymorphia.stepdefs

import csci.ooad.Maze
import csci.ooad.Polymorphia
import io.cucumber.java.en.Given
import io.cucumber.java.en.Then
import io.cucumber.java.en.When

class PolymorphiaStepDefs {

    World world


    PolymorphiaStepDefs(World world) {
        this.world = world;
    }


    @Given("I have a maze with the following attributes: {int} by {int} rooms, {int} of each entity, and {int} foods")
    public void iHaveAGameWithTheFollowingAttributes(int rows, int cols, int numEntities, int numFoods) {
        this.world.maze = Maze.Builder.getNewBuilder()
                .addAdventurersByNumber(numEntities)
                .addCowardsByNumber(numEntities)
                .addCreaturesByNumber(numEntities)
                .addDemonsByNumber(numEntities)
                .addFoodByNumber(numFoods)
                .addGluttonsByNumber(numEntities)
                .addKnightsByNumber(numEntities)
                .createNxMGridConnectedRooms(rows, cols)
                .distributeSequentially()
                .build();
    }
    @When("I run the maze")
    public void iRunTheMaze() {
        this.world.polymorphia = new Polymorphia(this.world.maze);
        this.world.polymorphia.play();
    }
    @Then("The game ends with either a winner, loser, or cat game")
    public void theGameEnds() {
        assert(this.world.polymorphia.isOver());
    }
    @Then("Either all creatures, all adventurers, or all entities should be dead")
    public checkIfAllCreaturesOrAllEntitiesOrBothAreDead() {
        assert(this.world.maze.areAllAdventurersDead() || this.world.maze.areAllCreaturesDead());
    }

}
