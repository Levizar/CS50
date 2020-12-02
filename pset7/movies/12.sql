SELECT m.title FROM (
    SELECT DISTINCT(movie_id) as movie_id, COUNT(*) as nb FROM people p
        INNER JOIN stars s on p.id = s.person_id
    WHERE p.name in ('Johnny Depp', 'Helena Bonham Carter')
    GROUP BY movie_id
    ) as t
INNER JOIN movies m on t.movie_id = m.id
where t.nb = 2;
