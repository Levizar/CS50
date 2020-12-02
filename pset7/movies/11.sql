SELECT m.title FROM people p
INNER JOIN stars s on p.id = s.person_id
INNER JOIN ratings r on s.movie_id = r.movie_id
INNER JOIN movies m on r.movie_id = m.id
WHERE p.name like 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;