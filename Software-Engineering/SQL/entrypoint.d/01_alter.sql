-- TODO: Make the column platform_id a FOREIGN KEY in the movies table.

ALTER TABLE movies
ADD CONSTRAINT platform_id FOREIGN KEY (platform_id) REFERENCES platforms (id);

ALTER TABLE movies_to_genres
ADD CONSTRAINT movie_id FOREIGN KEY (movie_id) REFERENCES movies (id);
ALTER TABLE movies_to_genres
ADD CONSTRAINT genre_id FOREIGN KEY (genre_id) REFERENCES genres (id);

ALTER TABLE movies_to_actors
ADD CONSTRAINT movie_id FOREIGN KEY (movie_id) REFERENCES movies (id);
ALTER TABLE movies_to_actors
ADD CONSTRAINT actor_id FOREIGN KEY (actor_id) REFERENCES actors (id);

/*
ALTER TABLE
ALTER TABLE
ALTER TABLE
ALTER TABLE
ALTER TABLE
*/