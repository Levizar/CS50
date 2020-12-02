SELECT p.name FROM movies m
INNER JOIN stars s ON m.id = s.movie_id
INNER JOIN people p ON s.person_id = p.id
WHERE m.title like 'Toy Story';

-- In average, this query seems to be slightly slower than the previous
-- SELECT p.name FROM movies m
-- INNER JOIN stars s ON m.id = s.movie_id AND m.title like 'Toy Story'
-- INNER JOIN people p ON s.person_id = p.id;

-- This query is VERY slow (6.5 sec vs 0.3 for the 2 others)
-- SELECT p.name FROM people p
-- INNER JOIN stars s ON p.id = s.person_id
-- INNER JOIN movies m ON m.id = s.movie_id
-- WHERE m.title like 'Toy Story';

