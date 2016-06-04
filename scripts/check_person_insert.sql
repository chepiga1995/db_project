CREATE OR REPLACE FUNCTION public.check_persons_insert()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
BEGIN
 IF char_length(NEW.first_name) = 0 OR char_length(NEW.last_name) = 0 THEN
    RAISE EXCEPTION 'Поля "Імя" і "Прізвище" мають бути не пустими.';
 END IF;
 IF char_length(NEW.login) = 0 THEN
      RAISE EXCEPTION 'Поле "Login" має бути не пустим.';
 END IF;
 IF not NEW.access_type in ('hr', 'worker', 'manager', 'ceo') THEN
     RAISE EXCEPTION 'Не коректне значення виду доступу';
 END IF;
 IF not NEW.phone_number ~ '^\([0-9]{2}\)-[0-9]{2}-[0-9]{2}-[0-9]{3}$' THEN
    RAISE EXCEPTION 'Не коректний номер телефону';
 END IF;
 RETURN NEW;
END;
$function$
