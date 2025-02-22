package csci.ooad.Commands;

import csci.ooad.Entities.Adventurer;
import csci.ooad.Entities.Creature;
import csci.ooad.Entities.Entity;
import csci.ooad.EventBus;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class FightCommand implements ICommand {
    private static final Logger logger = LoggerFactory.getLogger(FightCommand.class);
    private Entity adventurer;
    private Entity creature;
    public FightCommand(Entity adventurer, Entity creature) {this.adventurer = adventurer; this.creature = creature; }
    @Override
    public void execute() {
        int adventurerDiceRoll = adventurer.rollDie();
        int creatureDiceRoll = creature.rollDie();
        if (adventurerDiceRoll > creatureDiceRoll) {
            logger.info(String.format("\t%s %s damaged %s %s; their health changed from %.2f to %.2f", adventurer.getEntityType(), adventurer.getName(), creature.getEntityType(), creature.getName(), creature.getHealth(), (creature.getHealth()-(adventurerDiceRoll - creatureDiceRoll) < 0) ? (0) : creature.getHealth()-(adventurerDiceRoll - creatureDiceRoll)));
            EventBus.getInstance().postMessage(EventBus.EventType.FightOutcome, String.format("\t%s %s damaged %s %s; their health changed from %.2f to %.2f", adventurer.getEntityType(), adventurer.getName(), creature.getEntityType(), creature.getName(), creature.getHealth(), (creature.getHealth()-(adventurerDiceRoll - creatureDiceRoll) < 0) ? (0) : creature.getHealth()-(adventurerDiceRoll - creatureDiceRoll)));
            creature.applyDamage(adventurerDiceRoll - creatureDiceRoll);
        } else if (adventurerDiceRoll < creatureDiceRoll) {
            logger.info(String.format("\t%s %s damaged %s %s; their health changed from %.2f to %.2f", creature.getEntityType(), creature.getName(), adventurer.getEntityType(), adventurer.getName(), adventurer.getHealth(), (adventurer.getHealth()-(creatureDiceRoll - adventurerDiceRoll) < 0) ? (0) : adventurer.getHealth()-(creatureDiceRoll - adventurerDiceRoll)));
            EventBus.getInstance().postMessage(EventBus.EventType.FightOutcome, String.format("\t%s %s damaged %s %s; their health changed from %.2f to %.2f", creature.getEntityType(), creature.getName(), adventurer.getEntityType(), adventurer.getName(), adventurer.getHealth(), (adventurer.getHealth()-(creatureDiceRoll - adventurerDiceRoll) < 0) ? (0) : adventurer.getHealth()-(creatureDiceRoll - adventurerDiceRoll)));
            adventurer.applyDamage(creatureDiceRoll - adventurerDiceRoll);
        } else {
            logger.info(String.format("\t%s %s and %s %s both rolled a %d; no changes", adventurer.getEntityType(), adventurer.getName(), creature.getEntityType(), creature.getName(), adventurerDiceRoll));
            EventBus.getInstance().postMessage(EventBus.EventType.FightOutcome, String.format("\t%s %s and %s %s both rolled a %d; no changes", adventurer.getEntityType(), adventurer.getName(), creature.getEntityType(), creature.getName(), adventurerDiceRoll));
        }
        creature.applyDamage(Entity.DEFAULT_BATTLE_DAMAGE); // 0.5
        adventurer.applyDamage(Entity.DEFAULT_BATTLE_DAMAGE); // 0.5
        if (adventurer.isDead()) {
            logger.info(String.format("\t%s %s has died.", adventurer.getEntityType(), adventurer.getName()));
            EventBus.getInstance().postMessage(EventBus.EventType.Death, String.format("%s %s has been killed.", adventurer.getEntityType(), adventurer.getName()));
        } if (creature.isDead()) {
            logger.info(String.format("\t%s %s has died.", creature.getEntityType(), creature.getName()));
            EventBus.getInstance().postMessage(EventBus.EventType.Death, String.format("%s %s has been killed.", creature.getEntityType(), creature.getName()));
        }
        adventurer.setEntityState(Entity.EntityState.INACTIVE);
    }
}
