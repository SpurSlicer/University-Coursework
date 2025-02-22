package csci.ooad.Entities;

import csci.ooad.Commands.ICommand;
import csci.ooad.Maze;
import csci.ooad.Strategies.IStrategy;
import csci.ooad.Utility.Color;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ArmoredAdventurer extends Entity {
    private Adventurer adventurer;
    private double protection;
    private static final Logger logger = LoggerFactory.getLogger(ArmoredAdventurer.class);

    public ArmoredAdventurer(Adventurer adventurer) {
        this.adventurer = adventurer;
        this.protection = 0.0;
        this.adventurer.setEntityType(String.format("Armored%s", this.adventurer.entityType));
    }
    public double getProtection() { return this.protection; }
    public void addProtection(double protection) {
        this.protection += protection;
        this.adventurer.travelDamage += 0.1;
    }

    @Override
    public void applyDamage(double damage) {
        final double trueDamage = damage - this.protection;
        if (trueDamage > 0) {
            this.adventurer.applyDamage(trueDamage);
        }
    }
    // -----------
    @Override
    public String getName() { return this.adventurer.getName(); }
    // -----------
    @Override
    public double getHealth() { return this.adventurer.getHealth(); }
    // -----------
    @Override
    public void setHealth(int health) { this.adventurer.setHealth(health); }
    // -----------
    @Override
    public void applyHealth(double health) { this.adventurer.applyHealth(health); }
    // -----------
    @Override
    public String getInfo() {
        return String.format("%s(health: %.2f; prot: %.2f)", this.adventurer.name, this.adventurer.health, this.protection);
    }
    // -----------
    @Override
    public boolean isDead() { return this.adventurer.isDead(); }
    // -----------
    @Override
    public int rollDie() { return this.adventurer.rollDie(); }
    // -----------
    @Override
    public ICommand getAction(Maze.Room room) { return this.adventurer.strategy.getAction(this, room); }
    // -----------
    //@Override
    //protected void setAction(IStrategy strategy) { this.adventurer.setAction(strategy); }
    // -----------
    //@Override
    //protected void setTravelDamage(double travelDamage) { this.adventurer.setTravelDamage(travelDamage); }
    // -----------
    @Override
    public void applyTravelDamage() { this.adventurer.applyTravelDamage(); }
    // -----------
    @Override
    public EntityState getEntityState() { return this.adventurer.getEntityState(); }
    // -----------
    @Override
    public void setEntityState(EntityState state) { this.adventurer.setEntityState(state); }
    // -----------
    @Override
    public boolean canPlayTurn() { return this.adventurer.canPlayTurn(); }
    // -----------
    @Override
    public void setEntityType(String entityType) { this.adventurer.setEntityType(entityType); }
    // -----------
    @Override
    public String getEntityType() { return this.adventurer.getEntityType(); }
    // -----------
    @Override
    public void printInfo() { logger.info(String.format("  %s%s%s %s is here", (this.isDead()) ? Color.BLACK : Color.GREEN, this.getEntityType(), Color.RESET, this.getInfo())); }

}
