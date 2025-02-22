package csci.ooad.polymorphia.stepdefs


import csci.ooad.Entities.Adventurer
import csci.ooad.Entities.Creature
import csci.ooad.Maze
import io.cucumber.java.en.Given
import io.cucumber.java.en.Then
import io.cucumber.java.en.When

class AdventurerStepDefs {
    World world;

    AdventurerStepDefs(World world) {
        this.world = world;
    }

    @Given("I have an adventurer with {int} health")
    public void createAdventurerWithNHealth(int health) {
        this.world.adventurer = new Adventurer();
        this.world.adventurer.setHealth(health);
    }
    @When("The adventurer takes a fatal amount of damage")
    public void theAdventurerTakesAFatalAmountOfDamage() {
        this.world.adventurer.applyDamage(this.world.adventurer.getHealth());
    }
    @Then("The adventurer is considered to be dead")
    public void isTheAdventurerDead() {
        assert(this.world.adventurer.isDead());
    }

    @Given("I have an adventurer with the standard amount of health (5)")
    public void createAdventurerWith5Health() {
        this.world.adventurer = new Adventurer();
        this.world.adventurer.setHealth(5);
    }
    @When("The adventurer takes a nonfatal amount of damage")
    public void theAdventurerTakesANonFatalAmountOfDamage() {
        Random rand = new Random();
        final int damage = rand.nextInt(5);
        this.world.adventurer.applyDamage(damage);
    }
    @Then("The adventurer should still be alive")
    public void theAdventurerShouldStillBeAlive() {
        assert(!this.world.adventurer.isDead());
    }

    @Given("I have a basic maze with one coward, one food, and one standard creature in the same room")
    public void getBasicMazeForCoward() {
        this.world.maze = Maze.Builder.getNewBuilder()
            .addCowardsByNumber(1)
            .addCreaturesByNumber(1)
            .addFoodByNumber(1)
            .createNxMGridConnectedRooms(1, 2)
            .distributeSequentially()
            .build();
    }
    @When("I run one instance of the maze with a coward and creature in the same room")
    public void runCowardInstance() {
        this.world.maze.battle();
    }
    @Then("The coward fled rooms instead of fighting")
    public void didCowardFlee() {
        assert(this.world.maze.getAdventurers().get(0).getHealth() == (double)(Coward.DEFAULT_HEALTH - 0.5))
    }

    @Given("I have a basic maze with one glutton, one food, and one standard creature in the same room")
    public void getBasicMazeForGlutton() {
        this.world.maze = Maze.Builder.getNewBuilder()
                .addGluttonsByNumber(1)
                .addCreaturesByNumber(1)
                .addFoodByNumber(1)
                .createNxMGridConnectedRooms(1, 2)
                .distributeSequentially()
                .build();
    }
    @When("I run one instance of the maze with a glutton, food, and creature in the same room")
    public void runGluttonInstance() {
        this.world.maze.battle();
    }
    @Then("The glutton eats the food instead of fighting")
    public void didGluttonEatFood() {
        assert(this.world.maze.getAdventurers().get(0).getHealth() == (double)(Glutton.DEFAULT_HEALTH + 1))
    }

    @Given("I have a basic maze with one knight, one food, and one standard creature in the same room")
    public void getBasicMazeForKnight() {
        this.world.maze = Maze.Builder.getNewBuilder()
                .addKnightsByNumber(1)
                .addCreaturesByNumber(1)
                .addFoodByNumber(1)
                .createNxMGridConnectedRooms(1, 2)
                .distributeSequentially()
                .build();
    }
    @When("I run one instance of the maze with a knight and creature in the same room")
    public void runKnightInstance() {
        this.world.maze.battle();
    }
    @Then("The knight fights instead of eating or fleeing")
    public void didKnightFight() {
        assert(this.world.maze.getAdventurers().get(0).getHealth() < (double)(Knight.DEFAULT_HEALTH+1))
    }
}
