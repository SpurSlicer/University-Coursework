-- TODO: Get movies available on Hulu orderd by id.

SELECT movies.name FROM movies
    INNER JOIN platforms ON movies.platform_id = platforms.id
    WHERE platforms.name = 'Hulu'
    ORDER BY movies.id ASC;
/*
                             name
---------------------------------------------------------------
 Shadow Riders, The
 Saban, Son of Saban
 Smoke Signals
 American History X
 Cabinet of Dr. Caligari, The (Cabinet des Dr. Caligari., Das)
 Dawn Rider, The
(6 rows)
*/