package csci.ooad;

import csci.ooad.Observers.AudibleObserver;
import csci.ooad.Observers.TestObserver;
import csci.ooad.Utility.Color;
import org.slf4j.LoggerFactory;
import org.slf4j.Logger;
import csci.ooad.layout.intf.*;

import java.util.ArrayList;
import java.util.List;

public class Polymorphia implements IMazeSubject {
    IMazeObserver mazeObserver =
            MazeObserver.getNewBuilder("Polymorphia")
                    .useRadialLayoutStrategy()
                    .setDelayInSecondsAfterUpdate(2)
                    .build();
    private final Maze maze;
    private int turn;
    private State state;
    private final AudibleObserver observer;
    private final TestObserver testObserver;
    private static final Logger logger = LoggerFactory.getLogger(Polymorphia.class);
    public static enum State{ BATTLE, CAT, WIN, LOSE, ERROR }
// -----------
    public Polymorphia(Maze maze) {
        this.maze = maze;
        this.turn = 0;
        this.state = State.BATTLE;
        this.attach(this.mazeObserver);
        this.observer = new AudibleObserver(this.getEventsForObserver());
        this.testObserver = null;
        EventBus.getInstance().attach(this.observer);
    }
    public Polymorphia(Maze maze, TestObserver testObserver) {
        this.maze = maze;
        this.turn = 0;
        this.state = State.BATTLE;
        this.attach(this.mazeObserver);
        this.observer = new AudibleObserver(this.getEventsForObserver());
        this.testObserver = testObserver;
        EventBus.getInstance().attach(this.observer);
        EventBus.getInstance().attach(this.testObserver);
    }
// -----------
    private List<EventBus.EventType> getEventsForObserver() {
        List<EventBus.EventType> events = new ArrayList<>();
        events.add(EventBus.EventType.GameStatus);
        events.add(EventBus.EventType.TurnEnded);
        return events;
    }
// -----------
    /*
    * Main logic loop dependent on state machine (for state information, see PROJECT_README.md)
    */
    private void logicLoop() {
        if (turn == 0) notifyObservers("Game has begun");
        logger.info(String.format("Turn %d game state is %s\n", this.turn+1, this.state.name()));
        if (this.state == State.BATTLE) this.maze.battle();
        this.updateState();
        this.turn++;
        printInfo();
        if (this.state == State.WIN) {
            EventBus.getInstance().postMessage(EventBus.EventType.GameStatus, "The game is over. The adventurers left alive were " + this.maze.getAllAliveAdventurers().toString());
            logger.info(String.format("\n%s%sYay! %s Won!%s\n", Color.BLACK_BACKGROUND, Color.GREEN, "Adventurers" , Color.RESET));
        } else if (this.state == State.LOSE) {
            EventBus.getInstance().postMessage(EventBus.EventType.GameStatus, "The game is over. The creatures left alive were " + this.maze.getAllAliveCreatures().toString());
            logger.info(String.format("\n%s%sBoo, %s Lost :(%s\n", Color.BLACK_BACKGROUND, Color.RED, "Adventurers", Color.RESET));
        } else if (this.state == State.CAT) {
            EventBus.getInstance().postMessage(EventBus.EventType.GameStatus, "The game is over. No creatures or adventurers are alive.");
            logger.info(String.format("\n%s%sCat game! Both parties lose :/%s\n", Color.BLACK_BACKGROUND, Color.YELLOW, Color.RESET));
        }
        if (this.state != State.BATTLE) {
            logger.info(String.format("%s%s------------Logging------------%s\n", Color.BLACK_BACKGROUND, Color.WHITE, Color.RESET));
            if (this.state == State.LOSE) logger.info("The adventurers lost!");
            else if (this.state == State.WIN) logger.info("The adventurers won!");
            else if (this.state == State.CAT) logger.info("Cat game!");
            logger.info(String.format("\n%s%s-------------------------------%s\n", Color.BLACK_BACKGROUND, Color.WHITE, Color.RESET));
        }
        if (turn > 0) {
            notifyObservers("Turn " + this.turn + " has ended");
            EventBus.getInstance().postMessage(EventBus.EventType.TurnEnded, ("Turn " + this.turn + " has ended"));
        }
    }
// -----------
    public void play() {
        logger.info("Starting Play...");
        printInfo();
        while (this.state == State.BATTLE)
            logicLoop();
    }
// -----------
    public void printInfo() {
        if (this.turn > 0) logger.info(String.format("%s%s-------------------------------%s", Color.BLACK_BACKGROUND, Color.WHITE, Color.RESET));
        logger.info(String.format("\n%s%s%s%s turn %s%d%s\n", Color.BLACK_BACKGROUND, Color.rainbowify("Polymorphia MAZE:"), Color.BLACK_BACKGROUND, Color.WHITE, Color.PURPLE, this.turn, Color.RESET));
        this.maze.printRoomInfo();
        if (this.state == State.BATTLE) logger.info(String.format("%s%s------------Logging------------%s\n", Color.BLACK_BACKGROUND, Color.WHITE, Color.RESET));
    }
// -----------
    public boolean isOver() { return (this.state != State.BATTLE); }
// -----------
    public void updateState() {
        if (this.maze.areAllCreaturesDead() && this.maze.areAllAdventurersDead()) this.state = State.CAT;
        else if (this.maze.areAllCreaturesDead()) this.state = State.WIN;
        else if (this.maze.areAllAdventurersDead()) this.state = State.LOSE;
    }
    //public int getTurn() { return this.turn; }
// -----------
    @Override
    public IMaze getMaze() {
        return (IMaze)this.maze;
    }
}
