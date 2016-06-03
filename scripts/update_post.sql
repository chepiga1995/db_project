CREATE OR REPLACE FUNCTION public.update_post(_amount integer, _post_id integer)
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
    IF am_of_stuff != 0 and am_of_stuff >= _amount THEN
        RAISE EXCEPTION 'Кількість місць має бути більшою за кількість процюючих на цій посаді';
    END IF;
    -- update
    UPDATE structures SET date_out=now() WHERE date_out is NULL and post_id=_post_id;
    INSERT INTO structures(post_id, date_in, amount) 
            VALUES(_post_id, now(), _amount);
    RETURN am_of_stuff;
END;
$function$
