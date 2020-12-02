SELECT DISTINCT(p.name) FROM movies m
INNER JOIN stars s on m.id = s.movie_id
INNER JOIN people p on p.id = s.person_id
WHERE m.year == 2004
ORDER BY p.birth;