CREATE OR REPLACE FUNCTION public.check_vacation_type_insert()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
BEGIN
 IF char_length(NEW.description) = 0 OR char_length(NEW.name) = 0 THEN
    RAISE EXCEPTION 'Назва і Опис мають бути не пустими';
 END IF;
    RETURN NEW;
END;
$function$
