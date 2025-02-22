-- TODO: Verify that the data was correctly inserted into each table.

select count(*) from movies;
select count(*) from actors;
select count(*) from platforms;
select count(*) from genres;
select count(*) from movies_to_actors;
select count(*) from movies_to_genres;

/*
 count
-------
    26
(1 row)

 count
-------
    20
(1 row)

 count
-------
     7
(1 row)

 count
-------
     8
(1 row)

 count
-------
    61
(1 row)

 count
-------
    26
(1 row)
*/