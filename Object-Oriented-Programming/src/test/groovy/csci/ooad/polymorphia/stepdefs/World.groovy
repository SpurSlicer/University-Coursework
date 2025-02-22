package csci.ooad.polymorphia.stepdefs

import csci.ooad.Entities.Creature
import csci.ooad.Artifacts.Food
import csci.ooad.Maze
import csci.ooad.Observers.TestObserver
import csci.ooad.Polymorphia
import csci.ooad.Entities.Adventurer

class World {
    Polymorphia polymorphia
    Maze maze
    Adventurer adventurer;
    Creature creature;
    Food food;
    TestObserver testObserver;
}