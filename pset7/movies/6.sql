SELECT AVG(rating) FROM ratings r INNER JOIN movies m on r.movie_id = m.id AND m.year == 2012;