package csci.ooad;

import csci.ooad.Entities.Creature;
import csci.ooad.Entities.Entity;
import csci.ooad.Entities.EntityFactory;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

public class CreatureTest {
    @Test
    public void testCreatures() {
        // Creature
        Entity creature = EntityFactory.createCreaturesByNumber(1).get(0);
        assert (!creature.isDead());
        assert (creature.getHealth() == Creature.DEFAULT_HEALTH);
        creature.applyDamage(creature.getHealth());
        assert (creature.isDead());
        List<String> testName = new ArrayList<>();
        testName.add("test_name");
        Entity namedCreature = EntityFactory.createCreaturesByNames(testName).get(0);
        assert (namedCreature.getName().equals("test_name"));
        // Demon
        Entity demon = EntityFactory.createDemonsByNumber(1).get(0);
        assert (demon.getHealth() == 15.0);
        demon = EntityFactory.createDemonsByNames(testName).get(0);
        assert (demon.getName().equals("test_name"));
    }
}
