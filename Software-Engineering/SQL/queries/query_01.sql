-- TODO: Find the highest rated movie.
-- If there is a tie, return only one of highest rated movies.
SELECT name FROM movies 
    WHERE imdb_rating = (SELECT MAX(imdb_rating) from movies);
/*
     name
--------------
 Secret Honor
(1 row)
*/