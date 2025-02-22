-- TODO: Find the actor who has acted in the maximum number of movies.

SELECT name FROM actors 
    WHERE id = (SELECT MODE() WITHIN GROUP (ORDER BY actor_id) FROM movies_to_actors);
/*
        name
--------------------
 Leonardo di Caprio
(1 row)
*/