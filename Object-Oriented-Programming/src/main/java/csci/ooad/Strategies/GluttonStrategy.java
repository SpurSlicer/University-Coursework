package csci.ooad.Strategies;

import csci.ooad.Commands.*;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

public class GluttonStrategy implements IStrategy<Entity> {
    @Override
    public ICommand getAction(Entity adventurer, Maze.Room room) {
        if (room.hasFoods()) return CommandFactory.getEatCommand(adventurer, room.getAvailableFood(), room);
        else if (room.hasCreatures()) return CommandFactory.getFightCommand(adventurer, room.getRandomAliveCreature());
        else return CommandFactory.getMoveRoomsCommand(adventurer, room);
    }
}
