package csci.ooad.Entities;

import csci.ooad.Commands.ICommand;
import csci.ooad.Die;
import csci.ooad.Maze;
import csci.ooad.Strategies.IStrategy;

public abstract class Entity {
    protected String name;
    protected double health;
    protected Die die;
    protected IStrategy strategy;
    protected double travelDamage = 0.25;
    protected EntityState state;
    protected String entityType = "Entity";
    public enum EntityState { ACTIVE, INACTIVE, NULL };
    public static final double DEFAULT_BATTLE_DAMAGE = 0.5;
    // -----------
    public String getName() { return this.name; }
// -----------
    public double getHealth() { return this.health; }
// -----------
    public void setHealth(int health) { this.health = health; }
// -----------
    public void applyDamage(double damage) {
        this.health -= damage;
        if (this.health < 0) { // if the entity is dead, reset health to 0
            this.health = 0;
        }
    }
// -----------
    public void applyHealth(double health) { this.health += health; }
// -----------
    public String getInfo() {
        return String.format("%s(health: %.2f)", this.name, this.health);
    }
// -----------
    public boolean isDead() { return this.health == 0; }
// -----------
    public int rollDie() { return this.die.roll(); }
// -----------
    //public String getClassName() { return this.getClass().getName().replace("csci.ooad.Entities.", ""); }
// -----------
    public ICommand getAction(Maze.Room room) { return this.strategy.getAction(this, room); }
    protected void setAction(IStrategy strategy) { this.strategy = strategy; }
    protected void setTravelDamage(double travelDamage) { this.travelDamage = travelDamage; }
// -----------
    public void applyTravelDamage() { this.applyDamage(this.travelDamage); }
    public EntityState getEntityState() { return this.state; }
    public void setEntityState(EntityState state) { this.state = state; }
    public boolean canPlayTurn() { return ((this.state != EntityState.INACTIVE) && (!this.isDead())); }
    public void setEntityType(String entityType) { this.entityType = entityType; }
    public String getEntityType() { return this.entityType; }
    public abstract void printInfo();
}
