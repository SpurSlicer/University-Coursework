package csci.ooad;

import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.ArmoredAdventurer;
import csci.ooad.Entities.Entity;
import io.cucumber.java.bs.A;
import org.junit.jupiter.api.Test;

public class ArmoredAdventurerTest {
    @Test
    public void testArmoredAdventurers() {
        Adventurer adventurer = new Adventurer();
        ArmoredAdventurer armoredAdventurer = new ArmoredAdventurer(adventurer);
        armoredAdventurer.setEntityType("test");
        assert(armoredAdventurer.getEntityType().equals("test"));
        armoredAdventurer.setEntityState(Entity.EntityState.INACTIVE);
        assert(armoredAdventurer.getEntityState() == Entity.EntityState.INACTIVE);
        armoredAdventurer.setHealth(20);
        assert(armoredAdventurer.getHealth() == 20);
    }
}
