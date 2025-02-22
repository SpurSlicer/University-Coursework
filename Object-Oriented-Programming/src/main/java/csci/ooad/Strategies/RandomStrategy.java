package csci.ooad.Strategies;


import csci.ooad.Commands.*;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class RandomStrategy implements IStrategy<Entity> {
    @Override
    public ICommand getAction(Entity adventurer, Maze.Room room) {
        List<ICommand> possibleCommands = new ArrayList<>();
        if (room.hasCreatures()) possibleCommands.add(CommandFactory.getFightCommand(adventurer, room.getRandomAliveCreature()));
        if (room.hasFoods()) possibleCommands.add(CommandFactory.getEatCommand(adventurer, room.getAvailableFood(), room));
        if (room.hasArmor()) possibleCommands.add(CommandFactory.getWearArmorCommand(adventurer, room.getAvailableArmor(), room));
        if (room.getNumOfNeighboringRooms() > 0) possibleCommands.add(CommandFactory.getMoveRoomsCommand(adventurer, room));
        possibleCommands.add(CommandFactory.getNullCommand());
        Random rand = new Random();
        return possibleCommands.get(rand.nextInt(possibleCommands.size()));
    }
}
