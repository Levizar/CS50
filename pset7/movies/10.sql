SELECT p.name FROM ratings r
INNER JOIN directors d on r.movie_id = d.movie_id
INNER JOIN people p on p.id = d.person_id
WHERE r.rating >= 9.0;