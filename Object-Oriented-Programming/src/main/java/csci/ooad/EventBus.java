package csci.ooad;

import csci.ooad.Observers.IObserver;
import csci.ooad.Observers.TestObserver;

import java.util.List;
import java.util.ArrayList;

public class EventBus {
    public enum EventType {
        FightOutcome,
        AteSomething,
        TurnEnded,
        GameStatus,
        Death,
        Movement,
        All
    }
    private static EventBus eventBus;
    private List <IObserver> observers;
    private EventBus() {
        this.observers = new ArrayList<>();
    }
    public static EventBus getInstance() {
        if (eventBus == null) {
            eventBus = new EventBus();
        }
        return eventBus;
    }
    public void attach(IObserver observer) {
        this.observers.add(observer);
    }
    public void postMessage(EventType event, String eventDescription) {
        List<IObserver> relevantObservers = new ArrayList<>();
        for (IObserver observer : this.observers) {
            if (observer.isListeningToEvent(event) || observer.isListeningToEvent(EventType.All)) {
                if (observer.getClass() == TestObserver.class) observer.update(event, eventDescription);
                else relevantObservers.add(observer);
            }
        }
        if (!relevantObservers.isEmpty())
            relevantObservers.get(0).update(event, eventDescription);
        /*logger.info(this.observers.size());
        for (IObserver observer : relevantObservers) {
            observer.update(eventDescription);
        }*/
        //for (IObserver observer : this.observers) {
        //    if (observer.isListeningToEvent((event)))
        //        observer.update(eventDescription);
        //}
    }
}
