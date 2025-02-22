package csci.ooad;

import org.apache.commons.cli.*;

import csci.ooad.Maze;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
// -a 2 -c 2 -d 1 -f 3 -h 2 -m 3 -r 6
public class GameConfigurator {
    static int SECONDS_TO_PAUSE_BETWEEN_TURNS = 1;


    private final Maze.Builder mazeBuilder;
    private static final Logger logger = LoggerFactory.getLogger(GameConfigurator.class);


    GameConfigurator(CommandLine cmdLine) {
        mazeBuilder = Maze.Builder.getNewBuilder();
        try {
            buildMazeFromArguments(cmdLine);
        } catch (ParseException e) {
            logger.info(e.getMessage());
        }
    }


    public static void main(String[] args) {
        try {
            CommandLineParser parser = new DefaultParser();
            CommandLine cmdLine = parser.parse(getOptions(), args);
            GameConfigurator gameConfig = new GameConfigurator(cmdLine);
            gameConfig.createAndStartGame();
            System.exit(0);
        } catch (Exception e) {
            logger.info(e.getMessage());
            System.exit(-1);
        }
    }

    void buildMazeFromArguments(CommandLine cmdLine) throws ParseException {
        int numAdventurers = 1;
        int numCreatures = 1;
        int numDemons = 1;
        int numFoodItems = 2;
        int numHumans = 1;
        int numArmors = 2;
        int numRooms = 5;
        if (cmdLine.hasOption("a")) {
            numAdventurers = ((Number) cmdLine.getParsedOptionValue("a")).intValue();
        }
        if (cmdLine.hasOption("c")) {
            numCreatures = ((Number) cmdLine.getParsedOptionValue("c")).intValue();
        }
        if (cmdLine.hasOption("d")) {
            numDemons = ((Number) cmdLine.getParsedOptionValue("d")).intValue();
        }
        if (cmdLine.hasOption("f")) {
            numFoodItems = ((Number) cmdLine.getParsedOptionValue("f")).intValue();
        }
        if (cmdLine.hasOption("h")) {
            numHumans = ((Number) cmdLine.getParsedOptionValue("h")).intValue();
        }
        if (cmdLine.hasOption("m")) {
            numArmors = ((Number) cmdLine.getParsedOptionValue("m")).intValue();
        }
        if (cmdLine.hasOption("r")) {
            numRooms = ((Number) cmdLine.getParsedOptionValue("r")).intValue();
        }
        mazeBuilder.addAdventurersByNumber(numAdventurers);
        mazeBuilder.addCreaturesByNumber(numCreatures);
        mazeBuilder.addDemonsByNumber(numDemons);
        mazeBuilder.addFoodByNumber(numFoodItems);
        mazeBuilder.addHumansByNumber(numHumans);
        mazeBuilder.addArmorByNumber(numArmors);
        mazeBuilder.createNFullyConnectedRooms(numRooms);
        mazeBuilder.distributeRandomly();
    }

    public void createAndStartGame() {
        Polymorphia polymorphia = new Polymorphia(mazeBuilder.build());
        polymorphia.play();
    }


    static Options getOptions() {
        Option numAdventurers = Option.builder("a")
                .longOpt("numberOfAdventurers")
                .argName("numAdventurers")
                .hasArg()
                .numberOfArgs(1)
                .type(Number.class)
                .desc("the number of adventurers to place in the maze")
                .build();


        Option numCreatures = Option.builder("c")
                .longOpt("numberOfCreatures")
                .argName("numCreatures")
                .hasArg()
                .type(Number.class)
                .numberOfArgs(1)
                .desc("the number of creatures to place in the maze")
                .build();


        Option numDemons = Option.builder("d")
                .longOpt("numberOfDemons")
                .argName("numDemons")
                .hasArg()
                .type(Number.class)
                .numberOfArgs(1)
                .desc("the number of demons to place in the maze")
                .build();


        Option numFoodItems = Option.builder("f")
                .longOpt("numberOfFoodItems")
                .argName("numFoodItems")
                .hasArg()
                .numberOfArgs(1)
                .type(Number.class)
                .desc("the number of food items to place in the maze")
                .build();


        Option humanPlayer = Option.builder("h")
                .longOpt("humanPlayer")
                .argName("humanPlayerName")
                .hasArg()
                .numberOfArgs(1)
                .type(Number.class)
                .desc("the human player's name")
                .build();


        Option numArmoredSuits = Option.builder("m")
                .longOpt("numberOfArmoredSuits")
                .argName("numArmoredSuits")
                .hasArg()
                .numberOfArgs(1)
                .type(Number.class)
                .desc("the number of armored suits in the maze")
                .build();


        Option numRooms = Option.builder("r")
                .longOpt("numberOfRooms")
                .argName("numRooms")
                .hasArg()
                .numberOfArgs(1)
                .type(Number.class)
                .desc("the number of rooms in the maze")
                .build();


        Options options = new Options();
        options.addOption(numAdventurers);
        options.addOption(numCreatures);
        options.addOption(numDemons);
        options.addOption(numFoodItems);
        options.addOption(humanPlayer);
        options.addOption(numArmoredSuits);
        options.addOption(numRooms);


        return options;
    }
}