CREATE OR REPLACE FUNCTION public.check_skills_insert()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
BEGIN
 IF NEW.skill_id > 0 AND char_length(NEW.description) > 0 AND char_length(NEW.name) > 0 THEN
 RETURN NEW;
 END IF;
 RETURN null;
END;
$function$
