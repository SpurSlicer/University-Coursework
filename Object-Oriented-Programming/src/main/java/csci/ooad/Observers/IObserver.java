package csci.ooad.Observers;

import csci.ooad.EventBus;

public interface IObserver {
    abstract void update(EventBus.EventType eventType, String eventDescription);
    abstract boolean isListeningToEvent(EventBus.EventType event);
    //abstract List<String> getEvents();
}
