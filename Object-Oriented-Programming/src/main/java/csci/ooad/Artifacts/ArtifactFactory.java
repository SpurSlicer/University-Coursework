package csci.ooad.Artifacts;

import csci.ooad.Utility.Tuple;

import java.util.ArrayList;
import java.util.List;

public class ArtifactFactory {
// -----------
    public static List<Artifact> createFoodItemsByNumber(int foodNum) {
        List<Artifact> food = new ArrayList<>();
        for (int i = 0; i < foodNum; i++)
            food.add(new Food());
        return food;
    }
// -----------
    public static List<Artifact> createFoodItemsByNames(List<String> foodNames) {
        List<Artifact> food = new ArrayList<>();
        for (String foodName : foodNames)
            food.add(new Food(foodName));
        return food;
    }
// -----------
    public static List<Artifact> createArmorsByNumber(int armorNum) {
        List<Artifact> armors = new ArrayList<>();
        for (int i = 0; i < armorNum; i++)
            armors.add(new Armor());
        return armors;
    }
    // -----------
    public static List<Artifact> createArmorByInfo(List<Tuple<String, Integer>> armorInfo) {
        List<Artifact> armors = new ArrayList<>();
        for (Tuple<String, Integer> armorInfoPiece : armorInfo) {
            armors.add(new Armor(armorInfoPiece.first, armorInfoPiece.last));
        }
        return armors;
    }
// -----------
}
