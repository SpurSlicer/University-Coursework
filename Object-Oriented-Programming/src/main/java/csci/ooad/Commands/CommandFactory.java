package csci.ooad.Commands;

import csci.ooad.Artifacts.Armor;
import csci.ooad.Artifacts.Artifact;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Creature;
import csci.ooad.Artifacts.Food;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

public class CommandFactory {
// -----------
    public static ICommand getEatCommand(Entity adventurer, Food food, Maze.Room room) {
        return new EatCommand(adventurer, food, room);
    }
// -----------
    public static ICommand getWearArmorCommand(Entity adventurer, Armor armor, Maze.Room room) {
        return new WearArmorCommand(adventurer, armor, room);
    }
// -----------
    public static ICommand getFightCommand(Entity adventurer, Entity creature) {
        return new FightCommand(adventurer, creature);
    }
// -----------
    public static ICommand getMoveRoomsCommand (Entity entity, Maze.Room room) {
        return new MoveRoomsCommand(entity, room);
    }
// -----------
    public static ICommand getNullCommand () {
        return new NullComand();
    }
// -----------
}
