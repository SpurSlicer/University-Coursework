package csci.ooad.Commands;

import csci.ooad.Artifacts.Artifact;
import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Entity;
import csci.ooad.EventBus;
import csci.ooad.Artifacts.Food;
import csci.ooad.Maze;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class EatCommand implements ICommand {
    final static double DEFAULT_FOOD_HEALTH_INCREASE = 1.0;
    private static final Logger logger = LoggerFactory.getLogger(EatCommand.class);
    private Entity adventurer;
    private Food food;
    private Maze.Room room;
    public EatCommand(Entity adventurer, Food food, Maze.Room room) { this.adventurer = adventurer; this.food = food; this.room = room; }
    @Override
    public void execute() {
        logger.info(String.format("\t%s %s ate %s; their health changed from %.2f to %.2f", adventurer.getEntityType(), adventurer.getName(), food.getName(), adventurer.getHealth(), adventurer.getHealth()+1));
        EventBus.getInstance().postMessage(EventBus.EventType.AteSomething, (String.format("%s %s ate %s and their health is now %s", adventurer.getEntityType(), adventurer.getName(), food.getName(), String.valueOf((adventurer.getHealth()+1)))));
        adventurer.applyHealth(DEFAULT_FOOD_HEALTH_INCREASE);
        room.removeFood(food);
    }
}
