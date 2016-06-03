CREATE OR REPLACE FUNCTION public.close_post(_post_id integer)
 RETURNS integer
 LANGUAGE plpgsql
AS $function$
DECLARE
  am_of_stuff int;
  struct_id int;
  temp_post posts;
  temp_struc structures;
BEGIN
    -- validation
    BEGIN
        SELECT * INTO STRICT temp_post FROM posts WHERE posts.post_id = _post_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Посада % не знайдена', _post_id; 
    END;
    BEGIN
        SELECT * INTO STRICT temp_struc FROM structures WHERE structures.post_id = _post_id and structures.date_out is NULL;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Посада % не активна', _post_id; 
    END;
    SELECT count(s.stuff_id) INTO am_of_stuff FROM stuff as s WHERE s.post_id = _post_id and s.data_out is NULL;
    IF am_of_stuff != 0 THEN
        RAISE EXCEPTION 'На посаді працюють люди';
    END IF;
    -- update
    UPDATE structures SET date_out=now() WHERE date_out is NULL and post_id=_post_id;
    RETURN am_of_stuff;
END;
$function$
