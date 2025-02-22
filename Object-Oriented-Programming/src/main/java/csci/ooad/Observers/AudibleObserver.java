package csci.ooad.Observers;

import csci.ooad.EventBus;

import java.util.List;

public class AudibleObserver implements IObserver {
    //private Object observable;
    private List<EventBus.EventType> events;
    public AudibleObserver(/*Object observable, */List<EventBus.EventType> events) {
        //this.observable = observable;
        this.events = events;
    }
    @Override
    public void update(EventBus.EventType eventType, String eventDescription) {
        //String cmd = "cmd.exe nircmd speak text \"" + eventDescription + "\"";
        String cmd = "cmd /c C:\\Users\\grego\\Documents\\PROGRAMS\\nircmd\\nircmd.exe speak text \""+eventDescription+"\"";
        try {
            Process cmdProcess = Runtime.getRuntime().exec(cmd);
            cmdProcess.waitFor();
            //Thread.sleep(10000);
        } catch (Exception e) {
        }
    }

    @Override
    public boolean isListeningToEvent(EventBus.EventType event) {
        return this.events.contains(event);
    }
}
