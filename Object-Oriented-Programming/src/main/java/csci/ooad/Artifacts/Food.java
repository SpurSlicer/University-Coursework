package csci.ooad.Artifacts;

import csci.ooad.Utility.Color;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Food extends Artifact {
    // private String name;
    public final static int DEFAULT_FOOD_HEALTH_INCREASE = 1;
    //public static enum FoodState { VIABLE, EATEN };
    //private FoodState foodState;
// -----------
    public Food() {
        List<String> possibleNames = generatePossibleNames();
        Random rand = new Random();
        this.name = possibleNames.get(rand.nextInt(possibleNames.size()));
        //this.foodState = FoodState.VIABLE;
    }
// -----------
    public Food(String foodName) { this.name = foodName; /*this.foodState = FoodState.VIABLE;*/ }
    //public boolean isEaten() { return this.foodState == FoodState.EATEN; }
    //public void updateFoodState(FoodState foodstate) { this.foodState = foodstate; }
// -----------
    private List<String> generatePossibleNames() {
        List<String> names = new ArrayList<>();
        names.add("Banana");
        names.add("Lentil Soup");
        names.add("Sorbet");
        names.add("Apple Sauce");
        names.add("Pumpkin");
        names.add("Hummus Wrap");
        names.add("Guacamole");
        names.add("Cabbage");
        names.add("Peanut Butter");
        names.add("Almond Water");
        names.add("Exotic Butters");
        names.add("Overnight Oats");
        names.add("Mud Pie");
        names.add("Candy Rocks");
        names.add("Ghost Burger");
        return names;
    }
// -----------
}
