package csci.ooad.Strategies;

import csci.ooad.Commands.ICommand;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

public interface IStrategy<EntityType> {
    public ICommand getAction(EntityType entity, Maze.Room room);
}
