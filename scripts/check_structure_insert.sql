CREATE OR REPLACE FUNCTION public.check_structures_insert()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
BEGIN
 IF NEW.amount < 1 THEN
     RAISE EXCEPTION 'Кількість місць має бути додатньою';
 END IF;
 RETURN NEW;
END;
$function$
