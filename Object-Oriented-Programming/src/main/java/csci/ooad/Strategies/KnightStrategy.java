package csci.ooad.Strategies;

import csci.ooad.Commands.*;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

public class KnightStrategy implements IStrategy<Entity> {
    @Override
    public ICommand getAction(Entity adventurer, Maze.Room room) {
        if (room.hasArmor()) return CommandFactory.getWearArmorCommand(adventurer, room.getAvailableArmor(), room);
        else if (room.hasCreatures()) return CommandFactory.getFightCommand(adventurer, room.getHealthiestCreature());
        else if (room.hasFoods()) return CommandFactory.getEatCommand(adventurer, room.getAvailableFood(), room);
        else return CommandFactory.getMoveRoomsCommand(adventurer, room);
    }
}