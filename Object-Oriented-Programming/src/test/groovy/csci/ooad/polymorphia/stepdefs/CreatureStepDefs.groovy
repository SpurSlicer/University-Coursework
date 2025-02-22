package csci.ooad.polymorphia.stepdefs


import csci.ooad.Entities.Adventurer
import csci.ooad.Entities.Creature
import csci.ooad.Maze
import io.cucumber.java.en.Given
import io.cucumber.java.en.Then
import io.cucumber.java.en.When

class CreatureStepDefs {
    World world;

    CreatureStepDefs(World world) {
        this.world = world;
    }

    @Given("I have a creature with {int} health")
    public void createCreatureWithNHealth(int health) {
        this.world.creature = new Creature();
        this.world.creature.setHealth(health);
    }
    @When("The creature takes a fatal amount of damage")
    public void theCreatureTakesAFatalAmountOfDamage() {
        this.world.creature.applyDamage(this.world.creature.getHealth());
    }
    @Then("The creature is considered to be dead")
    public void isThecreatureDead() {
        assert(this.world.creature.isDead());
    }

    @Given("I have an creature with the standard amount of health (3)")
    public void createCreatureWith5Health() {
        this.world.creature = new Creature();
        this.world.creature.setHealth(3);
    }
    @When("The creature takes a nonfatal amount of damage")
    public void theCreatureTakesANonFatalAmountOfDamage() {
        Random rand = new Random();
        final int damage = rand.nextInt(3);
        this.world.creature.applyDamage(damage);
    }
    @Then("The creature should still be alive")
    public void theCreatureShouldStillBeAlive() {
        assert(!this.world.creature.isDead());
    }

    @Given("I have a maze with two rooms, one of each adventurer, one food, and one demon")
    public void setupDemonMaze() {
        this.world.maze = Maze.Builder.getNewBuilder()
                .addGluttonsByNumber(1)
                .addKnightsByNumber(1)
                .addAdventurersByNumber(1)
                .addCowardsByNumber(1)
                .addDemonsByNumber(1)
                .addFoodByNumber(1)
                .createNxMGridConnectedRooms(1, 2)
                .distributeFrontLoad()
                .build();
    }
    @When("I run the demon configured maze")
    public void runDemonConfiguredMaze() {
        this.world.maze.battle();
    }
    @Then("Every adventurer type fights the demon, i.e., their behaviors are overwritten")
    public void checkAdventurerBehavior() {
        List<Adventurer> adventurers = this.world.maze.getAdventurers();
        for (Adventurer adventurer : adventurers) {
            double adventurerHealth = adventurer.getHealth();
            double adventurerDefaultHealth = getDefaultHealth(adventurer.class);
            assert ((adventurerHealth != (adventurerDefaultHealth-0.25)) && (adventurerHealth != (adventurerDefaultHealth+1)))
        }
    }
    private double getDefaultHealth(Class classDef) {
        switch (classDef) {
            case Adventurer: return Adventurer.DEFAULT_HEALTH;
            case Glutton: return Glutton.DEFAULT_HEALTH;
            case Coward: return Coward.DEFAULT_HEALTH;
            case Knight: return Knight.DEFAULT_HEALTH;
            default: return 0;
        }
    }
}
