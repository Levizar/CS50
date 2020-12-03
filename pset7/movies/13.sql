SELECT DISTINCT(p2.name)
FROM stars s
         INNER JOIN (
-- movies for which Kevin Bacon stared
    SELECT movie_id
    FROM stars
             INNER JOIN people p ON p.id = stars.person_id
    WHERE p.name LIKE 'Kevin Bacon'
      AND birth = 1958
) AS kb_starred_movie ON s.movie_id = kb_starred_movie.movie_id
         INNER JOIN people p2 ON p2.id = s.person_id
WHERE (p2.name NOT LIKE 'Kevin Bacon' OR birth != 1958)


