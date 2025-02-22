-- TODO: Find 3 oldest movies. Return only THREE rows.

SELECT name FROM movies 
    ORDER BY year_of_release ASC LIMIT 3;
/*
                 name
---------------------------------------
 Mammy
 Angus
 Miguel and William (Miguel y William)
(3 rows)
*/