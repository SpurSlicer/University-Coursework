package csci.ooad;

import java.util.Random;

public class Die {
    private final Random die;
// -----------
    public Die() {
        this.die = new Random();
    }
// -----------
    public int roll() { return die.nextInt(6)+1; }
// -----------

    public static interface ICommand {
        public void execute();
    }
}
