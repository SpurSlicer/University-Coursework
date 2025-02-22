package csci.ooad;

import csci.ooad.layout.intf.IMaze;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

abstract class MazeAdaptor implements IMaze {
    //private Maze maze;
    abstract public Set<String> getRooms();
    // -----------
    abstract public Set<String> getNeighborsOf(String roomName);
    // -----------
    abstract public List<String> getContents(String roomName);
// -----------
}
