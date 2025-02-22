Feature: Check if mazes generate rooms with custom numbers correctly
  Check if maze can generate large or unusal numbers of rooms upon custom row and column amounts


  Scenario: Test if the maze generates with a custom grid of NxM rows and columns of rooms
    Given I have a maze with 10x20 rooms
    Then There are 10 times 20 room names
