-- TODO: Insert atleast 2 rows in each table

INSERT INTO actors (id, name, agency, active_since, location)
    VALUES 
    (
        21,
        'Idina Menzel',
        'Redwood', 
        2003,
        'New York'
    ),
    (
        22,
        'Kristen Bell',
        'Red Wood',
        2004,
        'New York'
    );
INSERT INTO platforms (id, name, viewership_cost)
    VALUES 
    (
        8,
        'Disney+_TEST',
        8
    ),
    (
        9,
        'Hulu_TEST',
        8
    );
INSERT INTO genres (id, name)
    VALUES 
    (
        9,
        'Fantasy_TEST'
    ),
    (
        10,
        'Ancient Fantasy_TEST'
    );
INSERT INTO movies (id, name , duration, year_of_release, gross_revenue, language, country, imdb_rating, platform_id)
    VALUES 
    (
        27,
        'Frozen',
        1.7,
        2013,
        1280000000,
        'English',
        'United States of America',
        7.4,
        9
    ),
    (
        28,
        'Frozen 2',
        1.7,
        2019,
        1453000000,
        'English',
        'United States of America',
        6.8,
        8
    );
INSERT INTO movies_to_actors (movie_id, actor_id)
    VALUES 
    (
        27,
        22
    ),
    (
        28,
        21
    );
INSERT INTO movies_to_genres (movie_id, genre_id)
    VALUES
    (
        27,
        9
    ),
    (
        28,
        10
    );
/*
INSERT 0 2
INSERT 0 2
INSERT 0 2
INSERT 0 2
INSERT 0 2
INSERT 0 2
*/