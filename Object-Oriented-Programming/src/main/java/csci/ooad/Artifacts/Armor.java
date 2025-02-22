package csci.ooad.Artifacts;

import csci.ooad.Utility.Tuple;

import java.util.*;

public final class Armor extends Artifact { // make a record class pls babe
    //private string name;
    private final double protection;
    Armor() {
        Tuple<String, Integer> armorInfo = this.generateRandomArmorSet();
        this.name = armorInfo.first;
        this.protection = armorInfo.last;
    }
    Armor(String name, double protection) {
        this.name = name;
        this.protection = protection;
    }
    public double getProtection() { return this.protection; }
    private Tuple<String, Integer> generateRandomArmorSet() {
        List<String> armorNames = new ArrayList<>();
        armorNames.add("Bronze Armor");
        armorNames.add("Silver Armor");
        armorNames.add("Gold Armor");
        armorNames.add("Diamond Armor");
        final Random rand = new Random();
        final int randomArmorIndex = rand.nextInt(armorNames.size());
        return new Tuple<String, Integer>(armorNames.get(randomArmorIndex), randomArmorIndex+1);
    }
}
