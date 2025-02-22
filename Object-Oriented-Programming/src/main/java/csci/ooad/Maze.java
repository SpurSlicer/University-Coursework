package csci.ooad;

import java.util.*;

import csci.ooad.Artifacts.Armor;
import csci.ooad.Artifacts.Artifact;
import csci.ooad.Artifacts.ArtifactFactory;
import csci.ooad.Artifacts.Food;
import csci.ooad.Commands.ICommand;
import csci.ooad.Entities.*;
import csci.ooad.Observers.AudibleObserver;
import csci.ooad.Utility.Color;
import csci.ooad.Utility.Tuple;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Maze extends MazeAdaptor {
    private final List<Entity> adventurers;
    private final List<Entity> creatures;
    private final List<Room> rooms;
    private final List<Artifact> foods;
    private final List<Artifact> armors;
    public enum DistributionPattern {
        SEQUENTIAL,
        RANDOM,
        FRONT_LOAD
    }
    public enum RoomConnectionPattern {
        FULL,
        GRID
    }
    private static class RoomInfo {
        public DistributionPattern distributionPattern = DistributionPattern.SEQUENTIAL;
        public RoomConnectionPattern roomConnectionPattern = RoomConnectionPattern.GRID;
        public int roomRowsNum = 1;
        public int roomColsNum = 1;
    }
    private Maze(List<Entity> adventurers, List<Entity> creatures, RoomInfo roomInfo, List<Artifact> foods, List<Artifact> armors) {
        this.adventurers = adventurers;
        this.creatures = creatures;
        this.foods = foods;
        this.armors = armors;
        this.rooms = generateRooms(roomInfo);
        distributeEverythingAmongstRooms(roomInfo.distributionPattern);
    }
    private void distributeEverythingAmongstRooms(DistributionPattern distributionPattern) {
        final int adventurersNum = this.adventurers.size(), creaturesNum = this.creatures.size(), foodsNum = this.foods.size(), armorsNum = this.armors.size();
        switch (distributionPattern) {
            case SEQUENTIAL:
                for (int i = 0; i < adventurersNum; i++) rooms.get(i % rooms.size()).addAdventurer((Adventurer) adventurers.get(i));
                for (int i = 0; i < creaturesNum; i++) rooms.get(i % rooms.size()).addCreature((Creature)creatures.get(i));
                for (int i = 0; i < foodsNum; i++) rooms.get(i % rooms.size()).addFood((Food)foods.get(i));
                for (int i = 0; i < armorsNum; i++) rooms.get(i % rooms.size()).addArmor((Armor)armors.get(i));
                break;
            case RANDOM:
                Random rand = new Random();
                for (int i = 0; i < adventurersNum; i++)
                    rooms.get(rand.nextInt(rooms.size())).addAdventurer((Adventurer)adventurers.get(i));
                for (int i = 0; i < creaturesNum; i++)
                    rooms.get(rand.nextInt(rooms.size())).addCreature((Creature)creatures.get(i));
                for (int i = 0; i < foodsNum; i++) rooms.get(rand.nextInt(rooms.size())).addFood((Food)foods.get(i));
                for (int i = 0; i < armorsNum; i++) rooms.get(rand.nextInt(rooms.size())).addArmor((Armor)armors.get(i));
                break;
            case FRONT_LOAD:
                for (int i = 0; i < adventurersNum; i++)
                    rooms.get(0).addAdventurer((Adventurer) adventurers.get(i));
                for (int i = 0; i < creaturesNum; i++)
                    rooms.get(0).addCreature((Creature)creatures.get(i));
                for (int i = 0; i < foodsNum; i++) rooms.get(0).addFood((Food)foods.get(i));
                for (int i = 0; i < foodsNum; i++) rooms.get(0).addArmor((Armor)armors.get(i));
        }
    }
    private List<Room> generateRooms(RoomInfo roomInfo) {
        List<Room> rooms = new ArrayList<>();
        for (int i = 0; i < roomInfo.roomRowsNum * roomInfo.roomColsNum; i++)
            rooms.add(new Room(String.format("Room %d", i+1)));
        switch (roomInfo.roomConnectionPattern) {
            case FULL:
                for (int i = 0; i < rooms.size(); i++) {
                    for (int j = 0; j < rooms.size(); j++) {
                        if (i == j) continue;
                        else rooms.get(i).addNeighboringRoom(rooms.get(j));
                    }
                }
                break;
            case GRID:
                int index = 0;
                for (Room room : rooms) { // complicated loop for auto generating valid neighboring rooms in graph format
                    if (((index % roomInfo.roomRowsNum) - 1 > -1) && ((index % roomInfo.roomRowsNum) - 1 < roomInfo.roomRowsNum)) room.addNeighboringRoom(rooms.get(index - 1));
                    if (((index % roomInfo.roomRowsNum) + 1 > -1) && ((index % roomInfo.roomRowsNum) + 1 < roomInfo.roomRowsNum)) room.addNeighboringRoom(rooms.get(index + 1));
                    if ((index-roomInfo.roomRowsNum > -1)) room.addNeighboringRoom(rooms.get(index - roomInfo.roomRowsNum));
                    if ((index+roomInfo.roomRowsNum < rooms.size())) room.addNeighboringRoom(rooms.get(index + roomInfo.roomRowsNum));
                    index++;
                }
                break;
        }
        return rooms;
    }
    //public List<Adventurer> getAdventurers() { return this.adventurers; }
    //public List<Creature> getCreatures() { return this.creatures; }
// -----------
    /*public int getCurrentFoodCount() {
        int numFoods = 0;
        for (Room room : this.rooms) {
            numFoods += room.getFoods().size();
        }
        return numFoods;
    }*/
// -----------
    /*
     * Combat logic loop.
     */
    public void battle() {
        for (Room room : this.rooms) room.decideRoomAction();
        this.activateAllEntities(); // allows all adventurers to have a turn again
        /*if (allCreaturesDead && !allAdventurersDead) this.state = MazeState.ALL_CREATURES_DEAD;
        else if (!allCreaturesDead && allAdventurersDead) this.state = MazeState.ALL_ADVENTURES_DEAD;
        else if (allCreaturesDead && allAdventurersDead) this.state = MazeState.ALL_ENTITIES_DEAD;*/
    }
    public boolean areAllCreaturesDead() {
        boolean allCreaturesDead = true;
        for (Entity creature : this.creatures) {
            if (!creature.isDead()) {
                allCreaturesDead = false;
                break;
            }
        }
        return allCreaturesDead;
    }
// -----------
    public boolean areAllAdventurersDead() {
        boolean allAdventurersDead = true;
        for (Entity adventurer : this.adventurers) {
            if (!adventurer.isDead()) {
                allAdventurersDead = false;
                break;
            }
        }
        return allAdventurersDead;
    }
// -----------
    private void activateAllEntities() {
        for (Entity adventurer : this.adventurers) {
            if (adventurer.isDead() && adventurer.getEntityState() != Entity.EntityState.INACTIVE) adventurer.setEntityState(Entity.EntityState.INACTIVE);
            else adventurer.setEntityState(Entity.EntityState.ACTIVE);
        }
        for (Entity creature : this.creatures) {
            creature.setEntityState(Entity.EntityState.NULL);
        }
    }
// -----------
    public List<String> getAllAliveCreatures() {
        List<String> aliveCreatures = new ArrayList<>();
        for (Entity creature : this.creatures) {
            if (!creature.isDead()) aliveCreatures.add(creature.getName());
        }
        return aliveCreatures;
    }
// -----------
    public List<String> getAllAliveAdventurers() {
        List<String> aliveAdventurers = new ArrayList<>();
        for (Entity adventurer : this.adventurers) {
            if (!adventurer.isDead()) aliveAdventurers.add(adventurer.getName());
        }
        return aliveAdventurers;
    }
// -----------
    /*public Map<String, Integer> getMazeAttributes() {
        Map<String, Integer> entityCount = new HashMap<>();
        entityCount.put("Rooms", this.rooms.size());
        entityCount.put("Adventurer", 0);
        entityCount.put("Coward", 0);
        entityCount.put("Creature", 0);
        entityCount.put("Demon", 0);
        entityCount.put("Glutton", 0);
        entityCount.put("Knight", 0);
        entityCount.put("Foods", this.foods.size());
        for (Adventurer adventurer : this.adventurers)
            entityCount.put(adventurer.getEntityType(), entityCount.get(adventurer.getEntityType())+1);
        for (Creature creature : this.creatures)
            entityCount.put(creature.getEntityType(), entityCount.get(creature.getEntityType())+1);
        return entityCount;
    }*/
// -----------
    public void printRoomInfo() {
        for (Room room : this.rooms)
            room.printInfo();
    }
// -----------
    @Override
    public Set<String> getRooms() {
        Set<String> rooms = new HashSet<>();
        for (Room room : this.rooms) {
            rooms.add(room.getName());
        }
        return rooms;
    }
// -----------
    @Override
    public Set<String> getNeighborsOf(String roomName) {
        for (Room room : this.rooms) {
            if (room.getName().equals(roomName)) {
                return room.getNeighboringRoomNames();
            }
        }
        return new HashSet<>();
    }
// -----------
    @Override
    public List<String> getContents(String roomName) {
        for (Room room : this.rooms) {
            if (room.getName().equals(roomName)) {
                return room.getContents();
            }
        }
        return new ArrayList<>();

    }
// -----------
    // -----------
    public static class Builder {
        private int creaturesNum = 0;
        private int adventurersNum = 0;
        private int cowardsNum = 0;
        private int demonsNum = 0;
        private int gluttonsNum = 0;
        private int knightsNum = 0;
        private int humansNum = 0;
        private int foodNum = 0;
        private int armorNum = 0;
        private RoomInfo roomInfo = new RoomInfo();
        private final List<String> creatureNames = new ArrayList<>();
        private final List<String> adventurerNames = new ArrayList<>();
        private final List<String> cowardNames = new ArrayList<>();
        private final List<String> demonNames = new ArrayList<>();
        private final List<String> gluttonNames = new ArrayList<>();
        private final List<String> knightNames = new ArrayList<>();
        private final List<String> humanNames = new ArrayList<>();
        private final List<String> foodNames = new ArrayList<>();
        private final List<Tuple<String, Integer>> armorInfo = new ArrayList<>();
    // -----------
        public static Builder getNewBuilder() {
            return new Builder();
        }
    // ----------- All Builder Methods -----------
        public Builder createNFullyConnectedRooms (int rowsNum) { this.roomInfo.roomRowsNum = rowsNum; this.roomInfo.roomConnectionPattern = RoomConnectionPattern.FULL; return this; }
        public Builder createNxMGridConnectedRooms (int rowsNum, int colsNum) { this.roomInfo.roomRowsNum = rowsNum; this.roomInfo.roomColsNum = colsNum; this.roomInfo.roomConnectionPattern = RoomConnectionPattern.GRID; return this; }
        public Builder distributeSequentially() { this.roomInfo.distributionPattern = DistributionPattern.SEQUENTIAL; return this; }
        public Builder distributeRandomly() { this.roomInfo.distributionPattern = DistributionPattern.RANDOM; return this; }
        public Builder distributeFrontLoad() { this.roomInfo.distributionPattern = DistributionPattern.FRONT_LOAD; return this; }
        public Builder addFoodByNumber(int foodNum) { this.foodNum = foodNum; return this; }
        public Builder addArmorByNumber(int armorNum) { this.armorNum = armorNum; return this; }
        public Builder addCreaturesByNumber(int creaturesNum) { this.creaturesNum = creaturesNum; return this; }
        public Builder addAdventurersByNumber(int adventurersNum) { this.adventurersNum = adventurersNum; return this; }
        public Builder addCowardsByNumber(int cowardsNum) { this.cowardsNum = cowardsNum; return this; }
        public Builder addDemonsByNumber(int demonsNum) { this.demonsNum = demonsNum; return this; }
        public Builder addGluttonsByNumber(int gluttonsNum) { this.gluttonsNum = gluttonsNum; return this; }
        public Builder addKnightsByNumber(int knightsNum) { this.knightsNum = knightsNum; return this; }
        public Builder addFoodByNames (List<String> foodNames) { this.foodNames.addAll(foodNames); return this; }
        public Builder addHumansByNumber(int humansNum) { this.humansNum = humansNum; return this; }
        //public Builder addHumansByNames (List<String> humanNames) { this.humanNames.addAll(humanNames); return this; }
        public Builder addArmorByInfo (List<Tuple<String, Integer>> armorInfo) { this.armorInfo.addAll(armorInfo); return this; }
        public Builder addCreaturesByNames (List<String> creatureNames) { this.creatureNames.addAll(creatureNames); return this; }
        public Builder addAdventurersByNames (List<String> adventurerNames) { this.adventurerNames.addAll(adventurerNames); return this; }
        public Builder addCowardsByNames(List<String> cowardNames) { this.cowardNames.addAll(cowardNames); return this; }
        public Builder addDemonsByNames(List<String> demonNames) { this.demonNames.addAll(demonNames); return this; }
        public Builder addGluttonsByNames(List<String> gluttonNames) { this.gluttonNames.addAll(gluttonNames); return this; }
        public Builder addKnightsByNames(List<String> knightNames) { this.knightNames.addAll(knightNames); return this; }
        public Maze build() {
            List<Entity> adventurers = this.generateAdventurers();
            List<Entity> creatures = this.generateCreatures();
            //List<Room> rooms = this.generateRooms();
            List<Artifact> foods = this.generateFood();
            List<Artifact> armors = this.generateArmor();
            return new Maze(adventurers, creatures, this.roomInfo, foods, armors);
        }
    // -----------
        //private void addRoomByString(String roomName, List<Room> rooms) { super.addRoomByString(roomName, rooms); }
    // -----------
        private List<Entity> generateCreatures() {
            List<Entity> creatures = new ArrayList<>();
            if (this.creaturesNum > 0) creatures.addAll(EntityFactory.createCreaturesByNumber(this.creaturesNum));
            if (!this.creatureNames.isEmpty()) creatures.addAll(EntityFactory.createCreaturesByNames(this.creatureNames));
            if (this.demonsNum > 0) creatures.addAll(EntityFactory.createDemonsByNumber(this.demonsNum));
            if (!this.demonNames.isEmpty()) creatures.addAll(EntityFactory.createDemonsByNames(this.demonNames));
            //for (Creature creature : creatures) creature.printInfo();
            return creatures;
        }
    // -----------
        private List<Entity> generateAdventurers() {
            List<Entity> adventurers = new ArrayList<>();
            if (this.adventurersNum > 0) adventurers.addAll(EntityFactory.createAdventurersByNumber(this.adventurersNum));
            if (!this.adventurerNames.isEmpty()) adventurers.addAll(EntityFactory.createAdventurersByNames(this.adventurerNames));
            if (this.cowardsNum > 0) adventurers.addAll(EntityFactory.createCowardsByNumber(this.cowardsNum));
            if (!this.cowardNames.isEmpty()) adventurers.addAll(EntityFactory.createCowardsByNames(this.cowardNames));
            if (this.gluttonsNum > 0) adventurers.addAll(EntityFactory.createGluttonsByNumber(this.gluttonsNum));
            if (!this.gluttonNames.isEmpty()) adventurers.addAll(EntityFactory.createGluttonsByNames(this.gluttonNames));
            if (this.knightsNum > 0) adventurers.addAll(EntityFactory.createKnightsByNumber(this.knightsNum));
            if (!this.knightNames.isEmpty()) adventurers.addAll(EntityFactory.createKnightsByNames(this.knightNames));
            if (this.humansNum > 0) adventurers.addAll(EntityFactory.createHumansByNumber(this.humansNum));
            //if (!this.humanNames.isEmpty()) adventurers.addAll(EntityFactory.createHumansByNames(this.humanNames));
            //for (Adventurer adventurer : adventurers) adventurer.printInfo();
            return adventurers;
        }
    // -----------
    private List<Artifact> generateFood() {
        List<Artifact> foods = new ArrayList<>();
        if (this.foodNum > 0) foods.addAll(ArtifactFactory.createFoodItemsByNumber((this.foodNum)));
        if (!this.foodNames.isEmpty()) foods.addAll(ArtifactFactory.createFoodItemsByNames(this.foodNames));
        return foods;
    }
    // -----------
    private List<Artifact> generateArmor() {
        List<Artifact> armor = new ArrayList<>();
        if (this.armorNum > 0) armor.addAll(ArtifactFactory.createArmorsByNumber((this.armorNum)));
        if (!this.armorInfo.isEmpty()) armor.addAll(ArtifactFactory.createArmorByInfo(this.armorInfo));
        return armor;
    }
    // -----------
    }
// -----------
    //public void test() { Room r = new Room("hi"); }
    // -----------
    public class Room {
        private final String name;
        private final List<Entity> creatures;
        private final List<Room> neighboringRooms;
        private final List<Entity> adventurers;
        private final List<Artifact> foods;
        private final List<Artifact> armors;
        private final AudibleObserver observer;
        private static final Logger logger = LoggerFactory.getLogger(Room.class);
    // -----------
        public Room(String name) {
            this.name = name;
            this.creatures = new ArrayList<>();
            this.neighboringRooms = new ArrayList<>();
            this.adventurers = new ArrayList<>();
            this.foods = new ArrayList<>();
            this.armors = new ArrayList<>();
            this.observer = new AudibleObserver(this.getEventsForObserver());
            EventBus.getInstance().attach(this.observer);
        }
        /*public static class Builder {
            private String roomName = "room";
            public static Builder getNewBuilder() { return new Builder(); }
            public Builder setRoomName(String name) { this.roomName = name; return this; }
            public Room Build() { return new Room(this.roomName); }
        }*/
    // -----------
        //public static Room createRoom(String string) { return new Room(string); }
        private List<EventBus.EventType> getEventsForObserver() {
            List<EventBus.EventType> events = new ArrayList<>();
            events.add(EventBus.EventType.AteSomething);
            events.add(EventBus.EventType.Death);
            events.add(EventBus.EventType.FightOutcome);
            events.add(EventBus.EventType.Movement);
            return events;
        }
    // -----------
        public void printInfo() {
            logger.info(String.format("%s%s%s:%s", Color.BLACK_BACKGROUND, Color.WHITE, this.name, Color.RESET));
            if (!this.adventurers.isEmpty()) { // print adventurer info
                for (Entity adventurer : this.adventurers)
                    adventurer.printInfo();
            }
            if (!this.creatures.isEmpty()) { // print creature info
                for (Entity creature : this.creatures)
                    creature.printInfo();
            }
            if (!this.foods.isEmpty()) { // print food info
                for (Artifact food : this.foods)
                    food.printInfo();
            }
            if (!this.armors.isEmpty()) { // print food info
                for (Artifact armor : this.armors)
                    armor.printInfo();
            }
        }
    // -----------
        public String getName() { return this.name; }
    // -----------
        private void addAdventurer(Entity adventurer) {
            this.adventurers.add(adventurer);
        }
    // -----------
        private void removeAdventurer(Entity adventurer) {
            this.adventurers.remove(adventurer);
        }
    // -----------
        private void removeCreature(Entity creature) {
            this.creatures.remove(creature);
        }

    // -----------
        //public List<Adventurer> getAdventurers() { return this.adventurers; }
    // -----------
        public boolean hasAdventurers() {
            boolean adventurersPresent = false;
            for (Entity adventurer : this.adventurers) { // check if there is at least one living adventurer
                if (adventurer.canPlayTurn()) {
                    adventurersPresent = true;
                    break;
                }
            }
            return adventurersPresent;
        }
    // -----------
        private void addCreature(Entity creature) {
            this.creatures.add(creature);
        }
    // -----------
        public boolean hasCreatures() {
            boolean creaturesPresent = false;
            for (Entity creature : this.creatures) { // check if there is at least one living creature
                if (creature.canPlayTurn()) {
                    creaturesPresent = true;
                    break;
                }
            }
            return creaturesPresent;
        }
    // -----------
        public Entity getHealthiestCreature() { // find the creature with the most health
            Entity healthiestCreature = null;
            for (Entity creature : this.creatures) {
                if (healthiestCreature == null) healthiestCreature = creature;
                else if (creature.getHealth() > healthiestCreature.getHealth()) healthiestCreature = creature;
            }
            if ((healthiestCreature == null) || healthiestCreature.isDead()) return null;
            else return healthiestCreature;
        }
    // -----------
    public Entity getHealthiestAdventurer() { // find the creature with the most health
        Entity healthiesAdventurer = null;
        for (Entity adventurer : this.adventurers) {
            if (healthiesAdventurer == null) healthiesAdventurer = adventurer;
            else if (adventurer.getHealth() > healthiesAdventurer.getHealth()) healthiesAdventurer = adventurer;
        }
        if ((healthiesAdventurer == null) || healthiesAdventurer.isDead()) return null;
        else return healthiesAdventurer;
    }
    // -----------
        public Entity getRandomAliveCreature() {
            List<Entity> aliveCreatures = this.getAliveCreatures();
            if (aliveCreatures.isEmpty()) return null;
            Random rand = new Random();
            return aliveCreatures.get(rand.nextInt(aliveCreatures.size()));
        }
    // -----------
        private List<Entity> getAliveCreatures() {
            List<Entity> aliveCreatures = new ArrayList<>();
            for (Entity creature : this.creatures) {
                if (!creature.isDead()) aliveCreatures.add(creature);
            }
            return aliveCreatures;
        }
    // -----------
        /*public int numOfCreaturesPresent() {
            int numOfCreatures = 0;
            for (Creature creature : this.creatures) {
                if (!creature.isDead()) numOfCreatures++;
            }
            return numOfCreatures;
        }*/
    // -----------
        private void addFood(Food food) {
            this.foods.add(food);
        }
        private void addArmor(Armor armor) {
            this.armors.add(armor);
        }
        public void removeFood(Food food) { this.foods.remove(food); }
        public void removeArmor(Armor armor) { this.armors.remove(armor); }
    // -----------
        //private List<Food> getFoods() { return this.foods; }
    // -----------
        public boolean hasFoods() { // check if any food is left in the room
            return !this.foods.isEmpty();
        }
    // -----------
        public boolean hasArmor() { // check if any food is left in the room
            return !this.armors.isEmpty();
        }
        public Food getAvailableFood() {
            if (!this.foods.isEmpty()) return (Food)this.foods.get(0);
            else return null;
        }
        public Armor getAvailableArmor() {
            if (!this.armors.isEmpty()) return (Armor)this.armors.get(0);
            else return null;
        }
    // -----------
        private void addNeighboringRoom(Room room) {
            this.neighboringRooms.add(room);
        }
        public void swapAdventurer(ArmoredAdventurer swap, Entity toBeSwapped) {
            if (toBeSwapped.getClass() == ArmoredAdventurer.class) return;
            int indexOfToBeSwapped = this.adventurers.indexOf(toBeSwapped);
            if (indexOfToBeSwapped < 0) logger.info(String.format("[ERROR] could not swap %s", toBeSwapped.getName()));
            else this.adventurers.set(indexOfToBeSwapped, swap);
        }
    // -----------
        public int getNumOfNeighboringRooms() {
            return this.neighboringRooms.size();
        }
    // -----------
        private Room getNeighboringRoom(int i) { return this.neighboringRooms.get(i); }
    // -----------
        public Set<String> getNeighboringRoomNames() {
            Set<String> roomNames = new HashSet<>();
            for (Room room : this.neighboringRooms) {
                roomNames.add(room.getName());
            }
            return roomNames;
        }
        public Room transferEntityToNeighbor(Entity entity, int neighboringRoomIndex) {
            if (this.adventurers.contains(entity)) {
                this.removeAdventurer(entity);
                this.getNeighboringRoom(neighboringRoomIndex).addAdventurer(entity);
                return this.getNeighboringRoom(neighboringRoomIndex);
            } else if (this.creatures.contains(entity)) {
                this.removeCreature(entity);
                this.getNeighboringRoom(neighboringRoomIndex).addCreature(entity);
                return this.getNeighboringRoom(neighboringRoomIndex);
            } else {
                logger.info(String.format("[ERROR] %s %s not found!!", entity.getEntityType(), entity.getName()));
                return null;
            }
        }
    // -----------
        public List<String> getContents() {
            List<String> contents = new ArrayList<>();
            for (Entity adventurer : this.adventurers)
                contents.add(String.format("%s %s(Health: %.2f)", adventurer.getEntityType(), adventurer.getName(), adventurer.getHealth()));
            for (Entity creature : this.creatures)
                contents.add(String.format("%s %s(Health: %.2f)", creature.getEntityType(), creature.getName(), creature.getHealth()));
            for (Artifact food : this.foods) {
                contents.add(food.getName());
            }
            for (Artifact armor : this.armors) {
                contents.add(armor.getName());
            }
            return contents;
        }
    // -----------
        private void decideRoomAction() {
            if (this.name.toLowerCase().startsWith("room")) logger.info(String.format("%s; Creatures %d; Adventurers %d; Food %d", this.getName(), this.creatures.size(), this.adventurers.size(), this.foods.size()));
            else logger.info(String.format("Room %s; Creatures %d; Adventurers %d; Food %d", this.getName(), this.creatures.size(), this.adventurers.size(), this.foods.size()));
            if (!this.hasCreatures() && !this.hasAdventurers()) return; // if the room is empty or only has creatures, do nothing
            //else if (!this.hasCreatures() && this.hasAdventurers()) this.determineConsumption();
            List<Entity> allCurrentCreatures = new ArrayList<>(this.creatures);
            for (Entity creature : allCurrentCreatures) {
                if (creature.canPlayTurn()) {
                    ICommand creatureCommand = creature.getAction(this);
                    if (creatureCommand != null) creatureCommand.execute();
                }
            }
            List<Entity> allCurrentAdventurers = new ArrayList<>(this.adventurers);
            for (Entity adventurer : allCurrentAdventurers) {
                if (adventurer.canPlayTurn()) {
                    ICommand adventurerCommand = adventurer.getAction(this);
                    adventurerCommand.execute();
                }
            }
        }
    // -----------
        /*private void determineConsumption() {
            List<Adventurer> sortedAdventurers = new ArrayList<>(this.adventurers);
            sortedAdventurers.sort(Comparator.comparing(Adventurer::getHealth));
            for (Adventurer adventurer : sortedAdventurers) {
                if (adventurer.canPlayTurn()) {
                    if (this.hasFoods()) { this.eatFood(adventurer); }
                    else { this.traverseRooms(adventurer); }
                }
            }
        }*/
    // -----------
        /*private void determineAttacks() {
            Creature demon = this.getDemonPresent();
            int adventurerIndex = 0;
            if (demon != null) { // if demon is present
                while ((this.adventurers.size() != adventurerIndex) && !demon.isDead()) {
                    Adventurer currentAdventurer = this.adventurers.get(adventurerIndex);
                    if (currentAdventurer.canPlayTurn()) {
                        this.battleLogic(currentAdventurer, demon);
                    }
                    adventurerIndex++;
                }
            } else {
                while ((this.adventurers.size() != adventurerIndex) && this.hasCreatures()) {
                    Adventurer currentAdventurer = this.adventurers.get(adventurerIndex);
                    if (!currentAdventurer.canPlayTurn()) {
                        adventurerIndex++;
                        continue;
                    }
                    if (currentAdventurer.getClass() == Adventurer.class) {
                        adventurerIndex++;
                        Creature strongestCreature = this.getHealthiestCreature();
                        if (strongestCreature == null) continue;
                        else this.battleLogic(currentAdventurer, strongestCreature);
                    } else if (currentAdventurer.getClass() == Knight.class) {
                        adventurerIndex++;
                        Creature randomCreature = this.getRandomAliveCreature();
                        if (randomCreature == null) continue;
                        else battleLogic(currentAdventurer, randomCreature);
                    } else if (currentAdventurer.getClass() == Coward.class) {
                        if (this.hasCreatures())  traverseRooms(currentAdventurer);
                    } else if (currentAdventurer.getClass() == Glutton.class) {
                        adventurerIndex++;
                        if (this.hasFoods()) this.eatFood(currentAdventurer);
                        else {
                            Creature randomCreature = this.getRandomAliveCreature();
                            if (randomCreature == null) continue;
                            else battleLogic(currentAdventurer, randomCreature);
                        }
                    } else {
                        logger.info("I SHOULD NEVER BE HERE!");
                    }
                }
            }
            this.determineConsumption();
        }*/
    // -----------
        /*private void battleLogic(Adventurer adventurer, Creature creature) {
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
            adventurer.setAdventurerState(Adventurer.AdventurerState.INACTIVE);
        }*/
    // -----------
        /*public void traverseRooms(Adventurer adventurer) {
            if (this.getNumOfNeighboringRooms() == 0) return;
            double previousAdventurerHealth = adventurer.getHealth();
            adventurer.applyTravelDamage();
            Random rand = new Random();
            final int newRoomIndex = rand.nextInt(this.getNumOfNeighboringRooms());
            logger.info(String.format("\t%s %s moved from %s to %s; their health changed from %.2f to %.2f", adventurer.getEntityType(), adventurer.getName(), this.getName(), this.getNeighboringRoom(newRoomIndex).getName(), previousAdventurerHealth, adventurer.getHealth()));
            this.getNeighboringRoom(newRoomIndex).addAdventurer(adventurer);
            this.removeAdventurer(adventurer);
            if (adventurer.isDead()) logger.info(String.format("\tAdventurer %s has died.", adventurer.getName()));
            adventurer.setAdventurerState(Adventurer.AdventurerState.INACTIVE);
        }*/
    // -----------
    }
// -----------
}
