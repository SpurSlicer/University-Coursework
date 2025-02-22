-- TODO: Top 3 highest grossing thriller movies.

SELECT movies.name FROM movies 
    INNER JOIN movies_to_genres on movies.id = movies_to_genres.movie_id
    INNER JOIN genres on movies_to_genres.genre_id = genres.id
    WHERE genres.name = 'Thriller'
    ORDER BY gross_revenue DESC LIMIT 3;
/*
      name
----------------
 Shutter Island
 Mammy
 Cover-Up
(3 rows)
*/