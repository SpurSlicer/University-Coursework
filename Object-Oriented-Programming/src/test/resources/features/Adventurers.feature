Feature: Check if adventurers behave correctly and if their subtypes exhibit the correct properties
  Verify if adventurers take damage and update state correctly
  Check if Gluttons prioritize food
  Check if Knights prioritize combat
  Check if Cowards favor fleeing

  Scenario: Test if adventurers die upon a fatal blow
    Given I have an adventurer with 10 health
    When The adventurer takes a fatal amount of damage
    Then The adventurer is considered to be dead

  Scenario: Test if adventurers stay alive upon a nonfatal blow
    Given I have an adventurer with the standard amount of health 5
    When The adventurer takes a nonfatal amount of damage
    Then The adventurer should still be alive

  Scenario: Test that cowards will switch rooms instead of fight or eat
    Given I have a basic maze with one coward, one food, and one standard creature in the same room
    When I run one instance of the maze with a coward and creature in the same room
    Then The coward fled rooms instead of fighting

  Scenario: Test that gluttons will eat food instead of fight or switch rooms
    Given I have a basic maze with one glutton, one food, and one standard creature in the same room
    When I run one instance of the maze with a glutton, food, and creature in the same room
    Then The glutton eats the food instead of fighting

  Scenario: Test that knights will fight instead of eat food or switch rooms
    Given I have a basic maze with one knight, one food, and one standard creature in the same room
    When I run one instance of the maze with a knight and creature in the same room
    Then The knight fights instead of eating or fleeing