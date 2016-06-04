CREATE OR REPLACE FUNCTION public.change_person(_salary integer, _post_id integer, _person_id integer)
 RETURNS integer
 LANGUAGE plpgsql
AS $function$
DECLARE
  stuff_id int;
  temp_post posts;
  temp_pers persons;
  temp_stuff stuff;
BEGIN
    -- validation
    BEGIN
        SELECT * INTO STRICT temp_post FROM posts WHERE posts.post_id = _post_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Посада % не знайдена', _post_id; 
    END;
    BEGIN
        SELECT * INTO STRICT temp_pers FROM persons WHERE persons.person_id = _person_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Людина % не знайдена', _person_id; 
    END;
    BEGIN
        SELECT * INTO STRICT temp_stuff FROM stuff WHERE stuff.person_id = _person_id and stuff.data_out is NULL;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Людина % не працює', _person_id; 
    END;
    -- update
    UPDATE stuff SET data_out=now() WHERE data_out is NULL and person_id = _person_id;
    INSERT INTO stuff(post_id, person_id, date_in, salary) 
            VALUES(_post_id, _person_id, now(), _salary);  
    RETURN stuff_id;
END;
$function$
