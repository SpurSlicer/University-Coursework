package csci.ooad.Artifacts;

import csci.ooad.Utility.Color;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Artifact {
    protected String name;
    public String getName() { return this.name; }
    protected static final Logger logger = LoggerFactory.getLogger(Artifact.class);
    public void printInfo() {
        logger.info(String.format("  %s%s%s", Color.YELLOW, this.getName(), Color.RESET));
    }
}
