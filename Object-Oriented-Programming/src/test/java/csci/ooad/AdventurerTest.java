
package csci.ooad;

import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.Entities.EntityFactory;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

public class AdventurerTest {
    @Test
    public void testAdventurers() {
        // Adventurer
        Entity adventurer = EntityFactory.createAdventurersByNumber(1).get(0);
        assert(!adventurer.isDead());
        assert(adventurer.getHealth() == Adventurer.DEFAULT_HEALTH);
        adventurer.applyDamage(adventurer.getHealth());
        assert(adventurer.isDead());
        List<String> testName = new ArrayList<>();
        testName.add("test_name");
        Entity namedAdventurer = EntityFactory.createAdventurersByNames(testName).get(0);
        assert(namedAdventurer.getName().equals("test_name"));
        // Coward
        Entity coward = EntityFactory.createCowardsByNumber(1).get(0);
        assert(coward.getHealth() == 5.0);
        coward = EntityFactory.createCowardsByNames(testName).get(0);
        assert(coward.getName().equals("test_name"));
        // Knight
        Entity knight = EntityFactory.createKnightsByNumber(1).get(0);
        assert(knight.getHealth() == 8.0);
        knight = EntityFactory.createKnightsByNames(testName).get(0);
        assert(knight.getName().equals("test_name"));
        // Glutton
        Entity glutton = EntityFactory.createGluttonsByNumber(1).get(0);
        assert(glutton.getHealth() == 3.0);
        glutton = EntityFactory.createGluttonsByNames(testName).get(0);
        assert(glutton.getName().equals("test_name"));
    }
}
