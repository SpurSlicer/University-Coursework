package csci.ooad.Strategies;

import csci.ooad.Commands.ICommand;
import csci.ooad.Entities.Creature;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

public class CreatureStrategy implements IStrategy<Entity> {
    @Override
    public ICommand getAction(Entity demon, Maze.Room room) {
        return null;
    }
}
