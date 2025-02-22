-- TODO: Actors from Missouri that starred in a Romcom ordered by name.

SELECT name FROM actors WHERE id = ANY
    (SELECT actor_id FROM movies_to_actors WHERE movie_id = ANY
        (SELECT id FROM movies WHERE id = ANY
            (SELECT movie_id FROM movies_to_genres WHERE genre_id = 
                (SELECT id from genres WHERE name = 'Romcom'))))
    AND location = 'Missouri'
    ORDER BY name ASC;
/*
  name
---------
 Malachi
(1 row)
*/