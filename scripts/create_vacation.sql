CREATE OR REPLACE FUNCTION public.create_vacation(_vacation_type_id integer, _person_id integer)
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
    BEGIN
        SELECT * INTO STRICT temp_vac FROM vacation_type WHERE vacation_type.vacation_type_id = _vacation_type_id;
        EXCEPTION 
            WHEN NO_DATA_FOUND THEN 
                RAISE EXCEPTION 'Тип відпустки % не знайдений', _vacation_type_id; 
    END;
    SELECT COUNT(vacation_id) INTO vac_ammount FROM vacations WHERE vacations.person_id = _person_id AND vacations.date_out IS NULL;
    IF vac_ammount > 0 THEN
        RAISE EXCEPTION 'Людина вже на відпустці';
    END IF;
    -- update
    INSERT INTO vacations(vacation_type_id, person_id, date_in) 
            VALUES(_vacation_type_id, _person_id, now());  
    RETURN vac_ammount;
END;
$function$
