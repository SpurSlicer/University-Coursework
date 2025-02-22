package csci.ooad;

import org.junit.jupiter.api.Test;

public class DieTest {
    @Test
    public void testDie() {
        Die die = new Die();
        double rolls = 0;
        for (int i = 0; i < 500; i++) rolls += die.roll();
        assert ((rolls/500) < 4 && (rolls/500) > 2); // test standardization of die roll
    }
}
