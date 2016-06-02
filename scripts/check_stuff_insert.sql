CREATE OR REPLACE FUNCTION public.check_stuff_insert()
 RETURNS trigger
 LANGUAGE plpgsql
AS $function$
DECLARE
    post posts;
    am_of_stuff int;
    am_of_stuct int;
BEGIN
    SELECT * INTO post FROM posts WHERE posts.post_id = NEW.post_id;
    IF not NEW.salary BETWEEN post.min_salary AND post.max_salary THEN
        RAISE EXCEPTION 'Зарплата має бути в діапазоні від % до % .', post.min_salary, post.max_salary;
    END IF;
    SELECT count(s.stuff_id) INTO am_of_stuff FROM stuff as s WHERE s.post_id = NEW.post_id and s.data_out is NULL;
    SELECT amount INTO am_of_stuct FROM structures as s WHERE s.post_id = NEW.post_id and s.date_out is NULL;
    IF am_of_stuff >= am_of_stuct THEN
        RAISE EXCEPTION 'Немає вільних місць на посаду % .', post.name;
    END IF;
 RETURN NEW;
END;
$function$
