Feature: Test if polymorphia runs and ends with a unit test
  Check if a standard room actually runs

  Scenario: Run a basic maze game
    Given I have a maze with the following attributes: 4 by 1 rooms, 1 of each entity, and 2 foods
    When I run the maze
    Then The game ends with either a winner, loser, or cat game
    Then Either all creatures, all adventurers, or all entities should be dead

