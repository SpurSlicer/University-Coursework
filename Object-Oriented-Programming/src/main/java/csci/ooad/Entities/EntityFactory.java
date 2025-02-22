package csci.ooad.Entities;

import csci.ooad.Strategies.*;

import java.util.ArrayList;
import java.util.List;

public class EntityFactory {
// ----------- Adventurers -----------
    public static List<Entity> createAdventurersByNumber(int numAdventurers) {
        List<Entity> adventurers = new ArrayList<>();
        for (int i = 0; i < numAdventurers; i++) {
            Adventurer adventurer = new Adventurer();
            adventurer.setAction(new RandomStrategy());
            adventurer.setEntityType("Adventurer");
            adventurers.add(adventurer);
        }
        return adventurers;
    }
// -----------
    public static List<Entity> createAdventurersByNames(List<String> adventurerNames) {
        List<Entity> adventurers = new ArrayList<>();
        for (String adventurerName : adventurerNames) {
            Adventurer adventurer = new Adventurer(adventurerName);
            adventurer.setAction((new RandomStrategy()));
            adventurer.setEntityType("Adventurer");
            adventurers.add(adventurer);
        }
        return adventurers;
    }
// -----------
    public static List<Entity> createKnightsByNumber(int numKnights) {
        List<Entity> knights = new ArrayList<>();
        final int knightHealth = 8;
        for (int i = 0; i < numKnights; i++) {
            Adventurer knight = new Adventurer();
            knight.setHealth(knightHealth);
            knight.setAction(new KnightStrategy());
            knight.setEntityType("Knight");
            knights.add(knight);
        }
        return knights;
    }
// -----------
    public static List<Entity> createKnightsByNames(List<String> knightNames) {
        List<Entity> knights = new ArrayList<>();
        final int knightHealth = 8;
        for (String knightName : knightNames){
            Adventurer knight = new Adventurer(knightName);
            knight.setHealth(knightHealth);
            knight.setAction(new KnightStrategy());
            knight.setEntityType("Knight");
            knights.add(knight);
        }
        return knights;
    }
    // -----------
    public static List<Entity> createHumansByNumber(int numHumans) {
        List<Entity> humans = new ArrayList<>();
        for (int i = 0; i < numHumans; i++) {
            Adventurer human = new Adventurer();
            human.setAction(new HumanStrategy());
            human.setEntityType("Human");
            humans.add(human);
        }
        return humans;
    }
    // -----------
    public static List<Entity> createHumansByNames(List<String> humanNames) {
        List<Entity> humans = new ArrayList<>();
        for (String humanName : humanNames){
            Adventurer human = new Adventurer(humanName);
            human.setAction(new HumanStrategy());
            human.setEntityType("Human");
            humans.add(human);
        }
        return humans;
    }
// -----------
    public static List<Entity> createCowardsByNumber(int numCowards) {
        List<Entity> cowards = new ArrayList<>();
        final double cowardTravelDamage = 0.5;
        for (int i = 0; i < numCowards; i++) {
            Adventurer coward = new Adventurer();
            coward.setAction(new CowardStrategy());
            coward.setTravelDamage(cowardTravelDamage);
            coward.setEntityType("Coward");
            cowards.add(coward);
        }
        return cowards;
    }
// -----------
    public static List<Entity> createCowardsByNames(List<String> cowardNames) {
        List<Entity> cowards = new ArrayList<>();
        final double cowardTravelDamage = 0.5;
        for (String cowardName : cowardNames){
            Adventurer coward = new Adventurer(cowardName);
            coward.setAction(new CowardStrategy());
            coward.setTravelDamage(cowardTravelDamage);
            coward.setEntityType("Coward");
            cowards.add(coward);
        }
        return cowards;
    }
// -----------
    public static List<Entity> createGluttonsByNumber(int numGluttons) {
        List<Entity> gluttons = new ArrayList<>();
        final int gluttonHealth = 3;
        for (int i = 0; i < numGluttons; i++) {
            Adventurer glutton = new Adventurer();
            glutton.setHealth(gluttonHealth);
            glutton.setAction(new GluttonStrategy());
            glutton.setEntityType("Glutton");
            gluttons.add(glutton);
        }
        return gluttons;
    }
// -----------
    public static List<Entity> createGluttonsByNames(List<String> gluttonNames) {
        List<Entity> gluttons = new ArrayList<>();
        final int gluttonHealth = 3;
        for (String gluttonName : gluttonNames){
            Adventurer glutton = new Adventurer(gluttonName);
            glutton.setHealth(gluttonHealth);
            glutton.setAction(new GluttonStrategy());
            glutton.setEntityType("Glutton");
            gluttons.add(glutton);
        }
        return gluttons;
    }
// ----------- Creatures -----------
public static List<Entity> createCreaturesByNumber(int numCreatures) {
    List<Entity> creatures = new ArrayList<>();
    for (int i = 0; i < numCreatures; i++) {
        Creature creature = new Creature();
        creature.setAction(new CreatureStrategy());
        creature.setEntityType("Creature");
        creatures.add(creature);
    }
    return creatures;
}
// -----------
    public static List<Entity> createCreaturesByNames(List<String> creatureNames) {
        List<Entity> creatures = new ArrayList<>();
        for (String creatureName : creatureNames) {
            Creature creature = new Creature(creatureName);
            creature.setAction(new CreatureStrategy());
            creature.setEntityType("Creature");
            creatures.add(creature);
        }
        return creatures;
    }
// -----------
    public static List<Entity> createDemonsByNumber(int numDemons) {
        List<Entity> demons = new ArrayList<>();
        final int demonHealth = 15;
        for (int i = 0; i < numDemons; i++) {
            Creature demon = new Creature();
            demon.setHealth(demonHealth);
            demon.setAction(new DemonStrategy());
            demon.setEntityType("Demon");
            demons.add(demon);
        }
        return demons;
    }
// -----------
    public static List<Entity> createDemonsByNames(List<String> demonNames) {
        List<Entity> demons = new ArrayList<>();
        final int demonHealth = 15;
        for (String demonName : demonNames) {
            Creature demon = new Creature(demonName);
            demon.setHealth(demonHealth);
            demon.setAction(new DemonStrategy());
            demon.setEntityType("Demon");
            demons.add(demon);
        }
        return demons;
    }
// -----------
}
