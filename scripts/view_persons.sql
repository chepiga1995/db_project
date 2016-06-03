SELECT p.person_id, p.first_name, p.last_name, p.login, p.access_type, p.birthday, NOT (s.stuff_id IS null) AS is_work, NOT (v.vacation_id IS null) AS is_vacation 
FROM persons p
LEFT JOIN vacations v ON v.person_id=p.person_id
LEFT JOIN stuff s ON s.person_id=p.person_id
WHERE s.data_out IS NULL AND v.date_out IS NULL