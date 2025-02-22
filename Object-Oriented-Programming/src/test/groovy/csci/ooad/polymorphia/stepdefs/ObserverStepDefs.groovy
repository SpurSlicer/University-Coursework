package csci.ooad.polymorphia.stepdefs

import csci.ooad.EventBus
import csci.ooad.Maze
import csci.ooad.Observers.TestObserver
import csci.ooad.Polymorphia
import io.cucumber.java.en.Given
import io.cucumber.java.en.Then
import io.cucumber.java.en.When

class ObserverStepDefs {
    World world;

    ObserverStepDefs(World world) {
        this.world = world;
    }

    @Given("I have a standard unit maze with {int} by {int} room(s), {int} of each entity, and {int} food(s)")
    public void createStandardUnitRoomDescribedAbove(int rows, int cols, int numEntities, int numFoods) {
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
    @When("The game is ran with a test observer linked")
    public void runGameWithTestObserverLinked() {
        this.world.testObserver = new TestObserver(EventBus.EventType.All);
        this.world.polymorphia = new Polymorphia(this.world.maze, this.world.testObserver);
        this.world.polymorphia.play();
    }
    @Then("The test observer should have received a game status update")
    public void didTestObserverRecieveAGameStateUpdate() {
        System.out.printf("Status: %b, Death Count: %d, Turn Count: %d, Food count: %d\n", this.world.testObserver.getGameStatus(), this.world.testObserver.getDeathsCount(), this.world.testObserver.getTurnCount(), this.world.testObserver.getConsumptionCount());
        assert(this.world.testObserver.getGameStatus());
    }
    @Then("The test observer should have a death event count matching the number of dead entities")
    public void didTestObserverHaveMatchingDeathCountToGame() {
        final int deathCount = 6 - (this.world.maze.getAllAliveAdventurers().size() + this.world.maze.getAllAliveCreatures().size());
        assert(deathCount == this.world.testObserver.getDeathsCount());
    }
    @Then("The test observer should have received a number of turn-change updates akin to the actual number of turns that played out in polymorphia")
    public void didTestObserverHaveMatchingTurnEventCountToPolymorphia() {
        assert(this.world.polymorphia.getTurn() == this.world.testObserver.getTurnCount());
    }
    @Then("Did test observer catch if food was eaten")
    public void wasFoodEaten() {
        if (this.world.maze.getCurrentFoodCount() == 1) assert(this.world.testObserver.getConsumptionCount() == 0);
        else assert(this.world.testObserver.getConsumptionCount() == 1);
    }
}
