CREATE OR REPLACE FUNCTION public.create_post(_name character varying, _description text, _min_salary integer, _max_salary integer, _amount integer, skill_ids integer[])
 RETURNS integer
 LANGUAGE plpgsql
AS $function$
DECLARE
  id int;
  s_id int;
  skill_id int;
  rec skills;
BEGIN
    -- validation
    FOREACH s_id IN ARRAY skill_ids
    LOOP
    BEGIN
        SELECT * INTO STRICT rec FROM skills WHERE skills.skill_id = s_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Вміння % не знайдено', s_id; 
    END;
    END LOOP; 
    -- insert
    INSERT INTO posts(name, description, max_salary, min_salary) 
        VALUES(_name, _description, _max_salary, _min_salary) RETURNING post_id INTO id;
    INSERT INTO structures(post_id, date_in, amount) 
        VALUES(id, now(), _amount);  
    FOREACH skill_id IN ARRAY skill_ids
    LOOP
        INSERT INTO con_posts_skills(skill_id, post_id) 
            VALUES(skill_id, id); 
    END LOOP;   
    RETURN id;
END;
$function$
