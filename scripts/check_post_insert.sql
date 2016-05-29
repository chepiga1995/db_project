CREATE OR REPLACE FUNCTION public.check_posts_insert()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
BEGIN
 IF char_length(NEW.description) = 0 OR char_length(NEW.name) = 0 THEN
    RAISE EXCEPTION 'Поля "Назва" і "Опис" мають бути не пустими.';
 END IF;
 IF NEW.min_salary < 1 OR  NEW.max_salary < 1 THEN
      RAISE EXCEPTION 'Максимальна та мінімальна зарплата має бути додатньою';
  END IF;
 IF NEW.min_salary > NEW.max_salary THEN
     RAISE EXCEPTION 'Максимальна зарплата має бути більшою за мінімальну';
 END IF;
 RETURN NEW;
END;
$function$
