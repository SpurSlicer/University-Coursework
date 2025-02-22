package csci.ooad.Entities;

import csci.ooad.Utility.Color;
import csci.ooad.Die;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Creature extends Entity {
    // protected String name;
    // protected int health;
    // protected Die die;
    public static final int DEFAULT_HEALTH = 3;
    private static final Logger logger = LoggerFactory.getLogger(Creature.class);
// -----------
    public Creature() {
        List<String> possibleNames = generatePossibleCreatureNames();
        Random rand = new Random();
        this.die = new Die();
        this.name = possibleNames.get(rand.nextInt(possibleNames.size()));
        this.health = Creature.DEFAULT_HEALTH;
        this.state = EntityState.NULL;
    }
    // -----------
    public Creature(String creatureName) {
        this.die = new Die();
        this.name = creatureName;
        this.health = Creature.DEFAULT_HEALTH;
        this.state = EntityState.NULL;
    }
// -----------
    private List<String> generatePossibleCreatureNames() {
        List<String> names = new ArrayList<>();
        names.add("Ogre");
        names.add("Slime");
        names.add("Mimic");
        names.add("Ghost");
        names.add("Skeleton");
        names.add("Golem");
        names.add("Zombie");
        names.add("Siren");
        return names;
    }
// -----------
    @Override
    public void printInfo() { logger.info(String.format("  %s%s%s %s is here", (this.isDead()) ? Color.BLACK : Color.RED, this.getEntityType(), Color.RESET, this.getInfo())); }
// -----------
}
