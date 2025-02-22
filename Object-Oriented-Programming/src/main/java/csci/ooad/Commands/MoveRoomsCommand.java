package csci.ooad.Commands;

import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Creature;
import csci.ooad.Entities.Entity;
import csci.ooad.EventBus;
import csci.ooad.Maze;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Random;

public class MoveRoomsCommand implements ICommand {
    private static final Logger logger = LoggerFactory.getLogger(MoveRoomsCommand.class);
    private Entity entity;
    private Maze.Room room;
    public MoveRoomsCommand(Entity entity, Maze.Room room) { this.entity = entity; this.room = room; }
    @Override
    public void execute() {
        if (room.getNumOfNeighboringRooms() == 0) return;
        double previousEntityHealth = entity.getHealth();
        entity.applyTravelDamage();
        Random rand = new Random();
        final int newRoomIndex = rand.nextInt(room.getNumOfNeighboringRooms());
        Maze.Room transferredRoom = room.transferEntityToNeighbor(entity, newRoomIndex);
        logger.info(String.format("\t%s %s moved from %s to %s; their health changed from %.2f to %.2f", entity.getEntityType(), entity.getName(), room.getName(), transferredRoom.getName(), previousEntityHealth, entity.getHealth()));
        EventBus.getInstance().postMessage(EventBus.EventType.Movement, String.format("%s %s moved to %s.", entity.getEntityType(), entity.getName(), transferredRoom.getName()));
        if (entity.isDead()) {
            logger.info(String.format("\t%s %s has died.", entity.getEntityType(), entity.getName()));
            EventBus.getInstance().postMessage(EventBus.EventType.Death, String.format("\t%s %s has died.", entity.getEntityType(), entity.getName()));
        }
        entity.setEntityState(Adventurer.EntityState.INACTIVE);
    }
}
