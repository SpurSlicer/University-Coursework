-- TODO: Actor with the overall highest revenue?
SELECT actors.name, SUM(movies.gross_revenue) AS revenue FROM actors
    INNER JOIN movies_to_actors ON movies_to_actors.actor_id = actors.id
    INNER JOIN movies ON movies_to_actors.movie_id = movies.id
    GROUP BY actors.name
    ORDER BY SUM(movies.gross_revenue) DESC
    LIMIT 1;
/*
        name        |  revenue
--------------------+-----------
 Leonardo di Caprio | 298665119
(1 row)
*/