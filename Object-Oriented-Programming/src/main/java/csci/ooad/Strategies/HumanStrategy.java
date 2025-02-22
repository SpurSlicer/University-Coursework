package csci.ooad.Strategies;

import csci.ooad.Commands.CommandFactory;
import csci.ooad.Commands.ICommand;
import csci.ooad.Commands.NullComand;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.Maze;

import csci.ooad.Utility.Tuple;
import org.apache.commons.cli.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class HumanStrategy implements IStrategy<Entity> {
    @Override
    public ICommand getAction(Entity adventurer, Maze.Room room) {
        List<Tuple<String, ICommand>> possibleCommands = new ArrayList<>();
        if (room.hasCreatures()) possibleCommands.add(new Tuple<String, ICommand>("FIGHT", CommandFactory.getFightCommand(adventurer, room.getRandomAliveCreature())));
        if (room.hasFoods()) possibleCommands.add(new Tuple<String, ICommand>("EAT", CommandFactory.getEatCommand(adventurer, room.getAvailableFood(), room)));
        if (room.hasArmor()) possibleCommands.add(new Tuple<String, ICommand>("PUT_ON_ARMOR", CommandFactory.getWearArmorCommand(adventurer, room.getAvailableArmor(), room)));
        if (room.getNumOfNeighboringRooms() > 0) possibleCommands.add(new Tuple<String, ICommand>("MOVE_ROOMS", CommandFactory.getMoveRoomsCommand(adventurer, room)));
        possibleCommands.add(new Tuple<String, ICommand>("DO_NOTHING", CommandFactory.getNullCommand()));
        System.out.printf("\t\tYou (%s %s) are in room \"%s\"\n\n", adventurer.getEntityType(), adventurer.getName(), room.getName());
        int optionIndex = 0;
        for (Tuple<String, ICommand> option : possibleCommands) {
            System.out.printf("\t\t\t%d. %s\n", optionIndex+1, option.first);
            optionIndex++;
        }
        while (true) {
            System.out.print("\n\t\tEnter your option: ");
            Scanner scanner = new Scanner(System.in);
            try {
                int choiceNumber = Integer.parseInt(scanner.nextLine());
                if ((choiceNumber < 1) || (choiceNumber > possibleCommands.size())) throw new RuntimeException();
                return possibleCommands.get(choiceNumber-1).last;
            } catch (NumberFormatException e) {
                System.out.print("\t\t\t[ERROR] please enter a valid integer");
            } catch (RuntimeException e) {
                System.out.printf("\t\t\t[ERROR] please enter a value between %d and %d inclusive", 1, possibleCommands.size());
            }
        }
    }
}
