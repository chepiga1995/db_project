CREATE group hr;
GRANT SELECT on ALL TABLES IN SCHEMA public to hr;
GRANT INSERT, UPDATE on vacations, stuff, persons, con_person_skill to hr;
GRANT UPDATE on ALL SEQUENCES IN SCHEMA public to hr;


create user ura1996 in group hr password ‘1230’;

CREATE group ceo;
GRANT SELECT on ALL TABLES IN SCHEMA public to ceo;
GRANT INSERT, UPDATE on vacation_type, posts, structures, skills, con_posts_skills to ceo;
GRANT UPDATE on ALL SEQUENCES IN SCHEMA public to ceo;	

create user ura1997 in group ceo password ‘1230’;