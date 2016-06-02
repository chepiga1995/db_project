SELECT p.name, p.description, p.min_salary, p.max_salary, s.amount, COUNT(st.stuff_id) AS work 
FROM posts p
INNER JOIN structures s ON s.post_id=p.post_id
LEFT JOIN stuff st ON st.post_id=p.post_id
WHERE s.date_out IS NULL AND st.data_out IS NULL 
GROUP BY p.name, p.description, p.min_salary, p.max_salary, s.amount;