Feature: Check if observers are actually being signaled correctly
  Check all appropriate events


  Scenario: Test if the functionality of observers
    Given I have a standard unit maze with 1 by 2 rooms, 1 of each entity, and 1 foods
    When The game is ran with a test observer linked
    Then The test observer should have received a game status update
    Then The test observer should have a death event count matching the number of dead entities
    Then The test observer should have received a number of turn-change updates akin to the actual number of turns that played out in polymorphia
    Then Did test observer catch if food was eaten