CREATE OR REPLACE FUNCTION public.create_person_past(_date_insert date, _first_name character varying, _last_name character varying, _education text, _salary integer, _login character varying, _email character varying, _skype character varying, _phone character varying, _access_type character varying, _birthday date, _post_id integer, skill_ids integer[])
 RETURNS integer
 LANGUAGE plpgsql
AS $function$
DECLARE
  id int;
  s_id int;
  skill_id int;
  am_of_stuct int;
  am_of_stuff int;
  temp_skill skills;
  temp_post posts;
  post posts;
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
    ALTER TABLE stuff DISABLE TRIGGER check_stuff;     
    SELECT * INTO post FROM posts WHERE posts.post_id = _post_id;
    IF not _salary BETWEEN post.min_salary AND post.max_salary THEN
        RAISE EXCEPTION 'Зарплата має бути в діапазоні від % до % .', post.min_salary, post.max_salary;
    END IF;
    SELECT count(s.stuff_id) INTO am_of_stuff FROM stuff as s WHERE s.post_id=_post_id and  s.data_out is NULL;
    BEGIN
    SELECT amount INTO STRICT am_of_stuct FROM structures as s WHERE s.post_id = _post_id 
        and s.date_out >= _date_insert and s.date_in < _date_insert;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Структура на % не знайдена', _date_insert; 
    END;
    IF am_of_stuff >= am_of_stuct THEN
        RAISE EXCEPTION 'Немає вільних місць на посаду % .Вільних місць на % -- % .', post.name, _date_insert, am_of_stuct;
    END IF;
    INSERT INTO stuff(post_id, person_id, date_in, salary) 
        VALUES(_post_id, id, now(), _salary); 
    ALTER TABLE stuff ENABLE TRIGGER check_stuff;      
    FOREACH skill_id IN ARRAY skill_ids
    LOOP
        INSERT INTO con_person_skill(skill_id, person_id) 
            VALUES(skill_id, id); 
    END LOOP;                    
    RETURN id;
END;
$function$
