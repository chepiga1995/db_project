CREATE OR REPLACE FUNCTION public.close_vacation(_person_id integer)
 RETURNS integer
 LANGUAGE plpgsql
AS $function$
DECLARE
  vac_ammount int;
  temp_vac vacation_type;
  temp_pers persons;
BEGIN
    -- validation
    BEGIN
        SELECT * INTO STRICT temp_pers FROM persons WHERE persons.person_id = _person_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Людина % не знайдена', _person_id; 
    END;
    SELECT COUNT(vacation_id) INTO vac_ammount FROM vacations WHERE vacations.person_id = _person_id AND vacations.date_out IS NULL;
    IF vac_ammount = 0 THEN
        RAISE EXCEPTION 'Людина не на відпустці';
    END IF;
    -- update
    UPDATE vacations SET date_out=now() WHERE date_out is NULL and person_id=_person_id; 
    RETURN vac_ammount;
END;
$function$
