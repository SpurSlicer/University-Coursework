package csci.ooad.Observers;

import csci.ooad.EventBus;

import java.util.ArrayList;
import java.util.List;

public class TestObserver implements IObserver {
    //private Object observable;
    private List<EventBus.EventType> events;
    private int deathsCount;
    private int turnCount;
    private boolean gameStatus;
    private int consumptionCount;
    private int battleCount;
    /*public TestObserver(List<EventBus.EventType> events) {
        //this.observable = observable;
        this.deathsCount = 0;
        this.turnCount = 0;
        this.gameStatus = false;
        this.consumptionCount = 0;
        this.battleCount = 0;
        this.events = events;
    }*/
    public TestObserver(/*Object observable, */EventBus.EventType event) {
        //this.observable = observable;
        this.deathsCount = 0;
        this.turnCount = 0;
        this.gameStatus = false;
        this.consumptionCount = 0;
        this.battleCount = 0;
        this.events = new ArrayList<>();
        this.events.add(event);
    }
    //public int getDeathsCount() { return this.deathsCount; }
    //public int getTurnCount() { return this.turnCount; }
    //public boolean getGameStatus() { return this.gameStatus; }
    //public int getConsumptionCount() { return this.consumptionCount; }
    //public int getBattleCount() { return this.battleCount; }
    @Override
    public void update(EventBus.EventType event, String eventDescription) {
        //System.out.println("I get here");
        switch (event) {
            case Death:
                this.deathsCount++;
                break;
            case TurnEnded:
                this.turnCount++;
                break;
            case GameStatus:
                this.gameStatus = true;
                break;
            case AteSomething:
                this.consumptionCount++;
                break;
            case FightOutcome:
                this.battleCount++;
                break;
            default:
        }
    }

    @Override
    public boolean isListeningToEvent(EventBus.EventType event) {
        return this.events.contains(event);
    }
}
