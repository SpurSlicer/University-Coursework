Feature: Check if creatures behave properly
  Check if creatures take damage properly
  Check if Demons lock all adventurers into place

  Scenario: Test if creatures die upon a fatal blow
    Given I have a creature with 20 health
    When The creature takes a fatal amount of damage
    Then The creature is considered to be dead

  Scenario: Test if creatures stay alive upon a nonfatal blow
    Given I have an creature with the standard amount of health 3
    When The creature takes a nonfatal amount of damage
    Then The creature should still be alive

  Scenario: Test if demons lock all adventurers into battle
    Given I have a maze with two rooms, one of each adventurer, one food, and one demon
    When I run the demon configured maze
    Then Every adventurer type fights the demon, i.e., their behaviors are overwritten