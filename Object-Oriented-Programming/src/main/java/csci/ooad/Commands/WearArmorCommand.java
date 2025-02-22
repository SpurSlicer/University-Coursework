package csci.ooad.Commands;

import csci.ooad.Artifacts.Armor;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.ArmoredAdventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.EventBus;
import csci.ooad.Maze;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class WearArmorCommand implements ICommand {
    private static final Logger logger = LoggerFactory.getLogger(WearArmorCommand.class);
    private Entity adventurer;
    private Armor armor;
    private Maze.Room room;
    public WearArmorCommand(Entity adventurer, Armor armor, Maze.Room room) {
        this.adventurer = adventurer;
        this.armor = armor;
        this.room = room;
    }
    @Override
    public void execute() {
        ArmoredAdventurer armoredAdventurer = (adventurer.getClass() == ArmoredAdventurer.class) ? (ArmoredAdventurer) adventurer : new ArmoredAdventurer((Adventurer)adventurer);
        logger.info(String.format("\t%s %s picked up %s; their protection changed from %.2f to %.2f", adventurer.getEntityType(), adventurer.getName(), armor.getName(), armoredAdventurer.getProtection(), armoredAdventurer.getProtection()+armor.getProtection()));
        EventBus.getInstance().postMessage(EventBus.EventType.AteSomething, (String.format("\t%s %s picked up %s; their protection changed from %.2f to %.2f", adventurer.getEntityType(), adventurer.getName(), armor.getName(), armoredAdventurer.getProtection(), armoredAdventurer.getProtection()+armor.getProtection())));
        armoredAdventurer.addProtection(armor.getProtection());
        room.removeArmor(armor);
        room.swapAdventurer(armoredAdventurer, this.adventurer);
    }
}
