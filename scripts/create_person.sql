CREATE OR REPLACE FUNCTION public.create_person(_first_name character varying, _last_name character varying, _education text, _salary integer, _login character varying, _email character varying, _skype character varying, _phone character varying, _access_type character varying, _birthday date, _post_id integer, skill_ids integer[])
 RETURNS integer
 LANGUAGE plpgsql
AS $function$
DECLARE
  id int;
  s_id int;
  skill_id int;
  temp_skill skills;
  temp_post posts;
BEGIN
    -- validation
    FOREACH s_id IN ARRAY skill_ids
    LOOP
    BEGIN
        SELECT * INTO STRICT temp_skill FROM skills WHERE skills.skill_id = s_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Вміння % не знайдено', s_id; 
    END;
    END LOOP; 
    BEGIN
        SELECT * INTO STRICT temp_post FROM posts WHERE posts.post_id = _post_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Посада % не знайдена', _post_id; 
    END;
    -- insert
    BEGIN
    INSERT INTO persons(first_name, last_name, education, login, email, skype, phone_number, access_type, birthday, date_in) 
        VALUES(_first_name, _last_name, _education, _login, _email, _skype, _phone, _access_type, _birthday, now()) RETURNING person_id INTO id;
    EXCEPTION
        WHEN unique_violation THEN 
            RAISE EXCEPTION 'Login % вже зайнятий', _login;  
    END;        
    INSERT INTO stuff(post_id, person_id, date_in, salary) 
        VALUES(_post_id, id, now(), _salary);  
    FOREACH skill_id IN ARRAY skill_ids
    LOOP
        INSERT INTO con_person_skill(skill_id, person_id) 
            VALUES(skill_id, id); 
    END LOOP;                    
    RETURN id;
END;
$function$
