CREATE OR REPLACE FUNCTION public.close_person(_person_id integer)
 RETURNS integer
 LANGUAGE plpgsql
AS $function$
DECLARE
  stuff_id int;
  temp_st stuff;
  temp_pers persons;
BEGIN
    -- validation
    BEGIN
        SELECT * INTO STRICT temp_pers FROM persons WHERE persons.person_id = _person_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Людина % не знайдена', _person_id; 
    END;
    BEGIN
        SELECT * INTO STRICT temp_st FROM stuff WHERE stuff.person_id = _person_id AND stuff.data_out IS NULL ;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Людина % не працює', _person_id; 
    END;
    -- update
    UPDATE stuff SET data_out=now() WHERE data_out is NULL and person_id = _person_id; 
    RETURN stuff_id;
END;
$function$
