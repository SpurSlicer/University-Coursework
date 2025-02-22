package csci.ooad;

import csci.ooad.Artifacts.Food;
import csci.ooad.Entities.*;
import csci.ooad.Observers.TestObserver;
import csci.ooad.Utility.Tuple;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

public class PolymorphiaTest {
    private final int NUM_ADVENTURERS = 1;
    private final int NUM_CREATURES_BIG = 2;
    private final int NUM_CREATURES_SMALL = 1;
    private final int NUM_FOODS_BIG = 8;
    private final int NUM_FOODS_SMALL = 3;
    private final int NUM_ARMORS_BIG = 8;
    private final int NUM_ARMORS_SMALL = 3;
    private final int TWO_BY_TWO = 4;
    private final int THREE_BY_THREE = 3;
    private final int THREE_BY_FOUR[] = {3, 4};
    @Test
    public void testGame() {
        Maze maze2x2 = this.full2x2Maze();
        TestObserver t = new TestObserver(EventBus.EventType.All);
        Polymorphia polymorphia2x2 = new Polymorphia(maze2x2);
        polymorphia2x2.play();
        //System.out.printf("Status: %b, Death Count: %d, Turn Count: %d, Food count: %d\n", t.getGameStatus(), t.getDeathsCount(), t.getTurnCount(), t.getConsumptionCount());
        assert (polymorphia2x2.isOver());
        Maze maze3x3 = this.grid3x3Maze();
        Polymorphia polymorphia3x3 = new Polymorphia(maze3x3, t);
        polymorphia3x3.play();
        assert (polymorphia3x3.isOver());
        Maze maze3x4 = this.grid3x4Maze();
        Polymorphia polymorphia3x4 = new Polymorphia(maze3x4, t);
        polymorphia3x4.play();
        assert (polymorphia3x4.isOver());
    }
    private List<String> getAdventurerNames(Class c) {
        List<String> adventurerNames = new ArrayList<>();
        for (int i = 0; i < NUM_ADVENTURERS; i++) adventurerNames.add(String.format("%s_%d", c.getName().replace("csci.ooad.", ""), i));
        return adventurerNames;
    }
    private List<String> getCreatureNames(Class c) {
        List<String> creatureNames = new ArrayList<>();
        for (int i = 0; i < NUM_CREATURES_BIG; i++) creatureNames.add(String.format("%s_%d", c.getName().replace("csci.ooad.", ""), i));
        return creatureNames;
    }
    private List<String> getFoodNames(Class c) {
        List<String> foodNames = new ArrayList<>();
        for (int i = 0; i < NUM_FOODS_BIG; i++) foodNames.add(String.format("%s_%d", c.getName().replace("csci.ooad.", ""), i));
        return foodNames;
    }
    private List<Tuple<String, Integer>> getArmorInfo() {
        List<Tuple<String, Integer>> armorNames = new ArrayList<>();
        for (int i = 0; i < NUM_ARMORS_BIG; i++)  armorNames.add(new Tuple<String, Integer>(String.format("Armor %d", i+1), i));
        return armorNames;
    }
    private Maze grid3x4Maze() {
        return Maze.Builder.getNewBuilder()
                .addAdventurersByNames(this.getAdventurerNames(Adventurer.class))
                .addCowardsByNumber(NUM_ADVENTURERS)
                .addKnightsByNumber(NUM_ADVENTURERS)
                .addGluttonsByNumber(NUM_ADVENTURERS)
                .addDemonsByNumber(NUM_CREATURES_BIG)
                .addArmorByNumber(NUM_ARMORS_BIG)
                .addFoodByNames(this.getFoodNames(Food.class))
                .createNxMGridConnectedRooms(THREE_BY_FOUR[0], THREE_BY_FOUR[1])
                .distributeFrontLoad()
                .build();
    }
    private Maze grid3x3Maze() {
        return Maze.Builder.getNewBuilder()
            .addAdventurersByNames(this.getAdventurerNames(Adventurer.class))
            .addCowardsByNames(this.getAdventurerNames(Adventurer.class))
            .addKnightsByNames(this.getAdventurerNames(Adventurer.class))
            .addGluttonsByNames(this.getAdventurerNames(Adventurer.class))
            .addCreaturesByNames(this.getCreatureNames(Creature.class))
            .addDemonsByNames(this.getCreatureNames(Creature.class))
            .addFoodByNames(this.getFoodNames(Food.class))
            .addArmorByInfo(this.getArmorInfo())
            .createNxMGridConnectedRooms(THREE_BY_THREE, THREE_BY_THREE)
            .distributeSequentially()
            .build();
    }
    private Maze full2x2Maze() {
        return Maze.Builder.getNewBuilder()
            .addAdventurersByNumber(NUM_ADVENTURERS)
            .addCowardsByNumber(NUM_ADVENTURERS)
            .addKnightsByNumber(NUM_ADVENTURERS)
            .addGluttonsByNumber(NUM_ADVENTURERS)
            .addCreaturesByNumber(NUM_CREATURES_SMALL)
            .addDemonsByNumber(NUM_CREATURES_SMALL)
            .addFoodByNumber(NUM_FOODS_SMALL)
            .addArmorByNumber(NUM_ARMORS_SMALL)
            .createNFullyConnectedRooms(TWO_BY_TWO)
            .distributeRandomly()
            .build();
    }
}
