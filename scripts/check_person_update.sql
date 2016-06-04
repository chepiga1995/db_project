CREATE OR REPLACE FUNCTION public.check_persons_update()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
BEGIN
 IF not NEW.phone_number ~ '^\([0-9]{2}\)-[0-9]{2}-[0-9]{2}-[0-9]{3}$' THEN
    RAISE EXCEPTION 'Не коректний номер телефону';
 END IF;
 RETURN NEW;
END;
$function$
