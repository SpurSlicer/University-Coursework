-- TODO: Find ALL the movies starring "Leonardo di Caprio".
SELECT movies.name FROM actors
    INNER JOIN movies_to_actors ON actors.id = movies_to_actors.actor_id
    INNER JOIN movies ON movies_to_actors.movie_id = movies.id
    WHERE actors.name = 'Leonardo di Caprio';
/*
                  name
-----------------------------------------
 Midsummer Night's Sex Comedy, A
 Secret Honor
 Ballad of a Soldier (Ballada o soldate)
 Satan's Tango (Sátántangó)
 Miracle
 Smoke Signals
 Shutter Island
(7 rows)
*/