package csci.ooad.Entities;

import csci.ooad.Utility.Color;
import csci.ooad.Die;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Adventurer extends Entity {
    // protected String name;
    // protected int health;
    // protected EntityState state;
    // protected Die die;
    // protected EntityState state;
    private double protection = 0;
    public static final int DEFAULT_HEALTH = 5;
    private static final Logger logger = LoggerFactory.getLogger(Adventurer.class);
// -----------
    public Adventurer() {
        List<String> possibleNames = this.generateNames();
        Random rand = new Random();
        this.die = new Die();
        this.name = possibleNames.get(rand.nextInt(possibleNames.size()));
        this.state = EntityState.ACTIVE;
        this.health = Adventurer.DEFAULT_HEALTH;
    }
// -----------
    public Adventurer(String adventurerName) {
        this.die = new Die();
        this.name = adventurerName;
        this.state = EntityState.ACTIVE;
        this.health = Adventurer.DEFAULT_HEALTH;
    }
// -----------
    private List<String> generateNames() {
        List<String> names = new ArrayList<>();
        names.add("Jarvis");
        names.add("Quote");
        names.add("Curly");
        names.add("Sam");
        names.add("Leo");
        names.add("Chase");
        names.add("Regret");
        names.add("Niko");
        names.add("Sun");
        names.add("Doomslayer");
        names.add("Spongebob");
        names.add("Finn");
        names.add("Princess Bubblegum");
        return names;
    }
// -----------
    @Override
    public void printInfo() { logger.info(String.format("  %s%s%s %s is here", (this.isDead()) ? Color.BLACK : Color.GREEN, this.getEntityType(), Color.RESET, this.getInfo())); }
// -----------
}
