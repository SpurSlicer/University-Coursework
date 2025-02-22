package csci.ooad.Strategies;

import csci.ooad.Commands.CommandFactory;
import csci.ooad.Commands.ICommand;
import csci.ooad.Commands.MoveRoomsCommand;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

public class CowardStrategy implements IStrategy<Entity> {
    @Override
    public ICommand getAction(Entity adventurer, Maze.Room room) {
        return CommandFactory.getMoveRoomsCommand(adventurer, room);
    }
}