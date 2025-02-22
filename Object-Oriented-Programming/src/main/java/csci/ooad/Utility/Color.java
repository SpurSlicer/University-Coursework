package csci.ooad.Utility;


/* SOURCE: https://stackoverflow.com/questions/5762491/how-to-print-color-in-console-using-system-out-println
*  - Used color codes and utility class structure
*/

public class Color {
    private static final boolean colorsEnabled = false;
    public static final String RESET = (Color.colorsEnabled) ? "\u001B[0m" : "";
    public static final String BLACK = (Color.colorsEnabled) ? "\u001B[30m" : "";
    public static final String RED = (Color.colorsEnabled) ? "\u001B[31m" : "";
    public static final String GREEN = (Color.colorsEnabled) ? "\u001B[32m" : "";
    public static final String YELLOW = (Color.colorsEnabled) ? "\u001B[33m" : "";
    public static final String BLUE = (Color.colorsEnabled) ? "\u001B[34m" : "";
    public static final String PURPLE = (Color.colorsEnabled) ? "\u001B[35m" : "";
    public static final String CYAN = (Color.colorsEnabled) ? "\u001B[36m" : "";
    public static final String BLACK_BACKGROUND = (Color.colorsEnabled) ? "\u001B[40m" : "";
    public static final String RED_BACKGROUND = (Color.colorsEnabled) ? "\u001B[41m" : "";
    public static final String GREEN_BACKGROUND = (Color.colorsEnabled) ? "\u001B[42m" : "";
    public static final String YELLOW_BACKGROUND = (Color.colorsEnabled) ? "\u001B[43m" : "";
    public static final String BLUE_BACKGROUND = (Color.colorsEnabled) ? "\u001B[44m" : "";
    public static final String PURPLE_BACKGROUND = (Color.colorsEnabled) ? "\u001B[45m" : "";
    public static final String CYAN_BACKGROUND = (Color.colorsEnabled) ? "\u001B[46m" : "";
    public static final String WHITE_BACKGROUND = (Color.colorsEnabled) ? "\u001B[47m" : "";
    public static final String WHITE = (Color.colorsEnabled) ? "\u001B[37m" : "";
// -----------
    public static String rainbowify(String str) {
        if (!Color.colorsEnabled) return str;
        StringBuilder rainbowString = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            switch (i % 6) { // RED, YELLOW, ..., PURPLE
                case 0: // RED
                    rainbowString.append(Color.RED);
                    break;
                case 1: // YELLOW
                    rainbowString.append(Color.YELLOW);
                    break;
                case 2: // GREEN
                    rainbowString.append(Color.GREEN);
                    break;
                case 3: // CYAN
                rainbowString.append(Color.CYAN);
                    break;
                case 4: // BLUE
                    rainbowString.append(Color.BLUE);
                    break;
                case 5: // PURPLE
                    rainbowString.append(Color.PURPLE);
                    break;
                default:
                    //("%s%s%sERROR!!%s\n", Color.RESET, Color.RED_BACKGROUND, Color.RESET, Color.RESET);
                    return null;
            }
            rainbowString.append(str.charAt(i));
        }
        rainbowString.append(Color.RESET);
        return rainbowString.toString();
    }
}
