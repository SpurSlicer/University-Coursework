package csci.ooad.Strategies;

import csci.ooad.Commands.CommandFactory;
import csci.ooad.Commands.FightCommand;
import csci.ooad.Commands.ICommand;
import csci.ooad.Commands.MoveRoomsCommand;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Creature;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

public class DemonStrategy implements IStrategy<Entity> {
    @Override
    public ICommand getAction(Entity demon, Maze.Room room) {
        Entity strongestAdventurer = room.getHealthiestAdventurer();
        if (strongestAdventurer == null) return CommandFactory.getMoveRoomsCommand(demon, room);
        else return CommandFactory.getFightCommand(strongestAdventurer, demon);
    }
}
