-- TODO: Find the platform with the most movies.

SELECT platforms.name, count(platforms.id) FROM platforms
    INNER JOIN movies ON platforms.id = movies.platform_id
    GROUP BY platforms.id
    ORDER BY count(platforms.id) DESC
    LIMIT 1;
/*
  name   | count
---------+-------
 Netflix |     7
(1 row)
*/