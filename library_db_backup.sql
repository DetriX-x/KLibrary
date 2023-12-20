--
-- PostgreSQL database dump
--

-- Dumped from database version 15.5 (Ubuntu 15.5-1.pgdg22.04+1)
-- Dumped by pg_dump version 16.1 (Ubuntu 16.1-1.pgdg22.04+1)

-- Started on 2023-12-20 14:04:49 MSK

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 4 (class 2615 OID 2200)
-- Name: public; Type: SCHEMA; Schema: -; Owner: pg_database_owner
--

CREATE SCHEMA public;


ALTER SCHEMA public OWNER TO pg_database_owner;

--
-- TOC entry 3477 (class 0 OID 0)
-- Dependencies: 4
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: pg_database_owner
--

COMMENT ON SCHEMA public IS 'standard public schema';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 214 (class 1259 OID 17259)
-- Name: authors; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.authors (
    author_id integer NOT NULL,
    name character varying(64) NOT NULL,
    surname character varying(64) NOT NULL,
    middlename character varying(64)
);


ALTER TABLE public.authors OWNER TO ketrix;

--
-- TOC entry 215 (class 1259 OID 17262)
-- Name: authors_author_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.authors ALTER COLUMN author_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.authors_author_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 216 (class 1259 OID 17263)
-- Name: books; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.books (
    book_id integer NOT NULL,
    edition_id integer NOT NULL,
    isbn character varying(32) NOT NULL,
    title character varying(64) NOT NULL,
    lang character varying(4) NOT NULL,
    year smallint NOT NULL,
    genre_id integer NOT NULL,
    quantity integer DEFAULT 10 NOT NULL
);


ALTER TABLE public.books OWNER TO ketrix;

--
-- TOC entry 217 (class 1259 OID 17266)
-- Name: books_authors; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.books_authors (
    book_id integer NOT NULL,
    author_id integer NOT NULL
);


ALTER TABLE public.books_authors OWNER TO ketrix;

--
-- TOC entry 218 (class 1259 OID 17269)
-- Name: books_book_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.books ALTER COLUMN book_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.books_book_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 219 (class 1259 OID 17270)
-- Name: editions; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.editions (
    edition_id integer NOT NULL,
    edition_name character varying(64) NOT NULL,
    country character varying(64)
);


ALTER TABLE public.editions OWNER TO ketrix;

--
-- TOC entry 220 (class 1259 OID 17273)
-- Name: editions_edition_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.editions ALTER COLUMN edition_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.editions_edition_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 221 (class 1259 OID 17274)
-- Name: genres; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.genres (
    genre_id integer NOT NULL,
    genre_name character varying(32) NOT NULL
);


ALTER TABLE public.genres OWNER TO ketrix;

--
-- TOC entry 222 (class 1259 OID 17277)
-- Name: genres_genre_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.genres ALTER COLUMN genre_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.genres_genre_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 223 (class 1259 OID 17278)
-- Name: librarians; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.librarians (
    librarian_id integer NOT NULL,
    login character varying(32) NOT NULL,
    password character varying(32) NOT NULL
);


ALTER TABLE public.librarians OWNER TO ketrix;

--
-- TOC entry 224 (class 1259 OID 17281)
-- Name: librarians_librarian_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.librarians ALTER COLUMN librarian_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.librarians_librarian_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 225 (class 1259 OID 17282)
-- Name: orders; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.orders (
    order_id integer NOT NULL,
    reader_id integer NOT NULL,
    book_id integer NOT NULL,
    date_start date NOT NULL,
    date_end date NOT NULL,
    status character varying(32) NOT NULL
);


ALTER TABLE public.orders OWNER TO ketrix;

--
-- TOC entry 226 (class 1259 OID 17285)
-- Name: orders_order_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.orders ALTER COLUMN order_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.orders_order_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 227 (class 1259 OID 17286)
-- Name: readers; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.readers (
    reader_id integer NOT NULL,
    login character varying(16) NOT NULL,
    password character varying(16) NOT NULL,
    phone character varying(16),
    email character varying(256)
);


ALTER TABLE public.readers OWNER TO ketrix;

--
-- TOC entry 228 (class 1259 OID 17289)
-- Name: readers_reader_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.readers ALTER COLUMN reader_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.readers_reader_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 229 (class 1259 OID 17290)
-- Name: reviews; Type: TABLE; Schema: public; Owner: ketrix
--

CREATE TABLE public.reviews (
    review_id integer NOT NULL,
    reader_id integer,
    book_id integer NOT NULL,
    rating integer NOT NULL,
    content text,
    review_datetime timestamp(0) without time zone NOT NULL
);


ALTER TABLE public.reviews OWNER TO ketrix;

--
-- TOC entry 230 (class 1259 OID 17295)
-- Name: reviews_review_id_seq; Type: SEQUENCE; Schema: public; Owner: ketrix
--

ALTER TABLE public.reviews ALTER COLUMN review_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.reviews_review_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 233 (class 1259 OID 17975)
-- Name: v_authors; Type: VIEW; Schema: public; Owner: ketrix
--

CREATE VIEW public.v_authors AS
 SELECT au.author_id,
    concat(au.surname, ' ', "left"((au.name)::text, 1), '.', "left"((au.middlename)::text, 1)) AS concat
   FROM public.authors au;


ALTER VIEW public.v_authors OWNER TO ketrix;

--
-- TOC entry 234 (class 1259 OID 17989)
-- Name: v_books; Type: VIEW; Schema: public; Owner: ketrix
--

CREATE VIEW public.v_books AS
 SELECT b.book_id,
    b.title,
    array_to_string(array_agg((((authors.name)::text || ' '::text) || (authors.surname)::text)), ', '::text) AS array_to_string,
    ge.genre_name,
    b.lang,
    b.year,
    e.edition_name,
    b.quantity,
    b.isbn
   FROM ((((public.books b
     LEFT JOIN public.books_authors ba ON ((ba.book_id = b.book_id)))
     LEFT JOIN public.authors USING (author_id))
     JOIN public.genres ge ON ((b.genre_id = ge.genre_id)))
     JOIN public.editions e ON ((b.edition_id = e.edition_id)))
  GROUP BY b.book_id, b.title, ge.genre_name, b.lang, b.year, e.edition_name, b.quantity, b.isbn;


ALTER VIEW public.v_books OWNER TO ketrix;

--
-- TOC entry 231 (class 1259 OID 17809)
-- Name: v_orders; Type: VIEW; Schema: public; Owner: ketrix
--

CREATE VIEW public.v_orders AS
 SELECT o.order_id,
    r.reader_id,
    r.login,
    b.book_id,
    b.title,
    o.date_start,
    o.date_end,
    o.status
   FROM ((public.orders o
     JOIN public.books b USING (book_id))
     JOIN public.readers r USING (reader_id));


ALTER VIEW public.v_orders OWNER TO ketrix;

--
-- TOC entry 232 (class 1259 OID 17824)
-- Name: v_reviews; Type: VIEW; Schema: public; Owner: ketrix
--

CREATE VIEW public.v_reviews AS
 SELECT r.review_id,
    r.reader_id,
    re.login,
    r.book_id,
    b.title,
    r.rating,
    r.content,
    (to_timestamp((r.review_datetime)::text, 'YYYY-MM-DD HH24:MI:SS'::text))::timestamp without time zone AS to_timestamp
   FROM ((public.reviews r
     LEFT JOIN public.readers re USING (reader_id))
     LEFT JOIN public.books b USING (book_id));


ALTER VIEW public.v_reviews OWNER TO ketrix;

--
-- TOC entry 3455 (class 0 OID 17259)
-- Dependencies: 214
-- Data for Name: authors; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (19, 'David', 'Tuba', 'Kishan');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (20, 'Palencia', 'Flanagan', 'Vijay');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (22, 'Luisita', 'McNab', 'Archelaos');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (24, 'Nikola', 'Helios', 'Steiner');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (26, 'Barney', 'Jaidev', 'Bergfalk');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (27, 'Athena ', 'Shain', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (28, 'Ivanka', 'Moe', 'Fitzsimmons');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (29, 'Christina', 'Jela', 'Sokol');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (31, 'Annice', 'Bahar', 'Trudu');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (32, 'Sigge', 'Luka', 'Lovrić');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (33, 'Jehovah', 'Simon', 'Klerx');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (34, 'Mari', 'Heli ', 'Hier');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (35, 'Szymon', 'Benny', 'Llywelyn');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (1, 'James', 'Clear', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (7, 'Victor', 'Pelevin', 'Olegovich');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (9, 'Ilya', 'Ilif', 'Arnoldovich');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (14, 'William', 'Golding', 'Jareld');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (15, 'Brem', 'Stoker', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (17, 'Maria', 'Korelli', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (18, 'Sergey', 'Povarin', 'Innokentievich');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (2, 'Стивен', 'Прата', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (3, 'Экхарт', 'Толле', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (4, 'Чарльз', 'Петцольд', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (8, 'Федор', 'Достоевский', 'Михайлович');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (16, 'Михаил', 'Булгаков', 'Афанасьевич');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (11, 'Николай', 'Гоголь', 'Васильевич');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (5, 'Robert', 'Green', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (13, 'Борис', 'Стругацкий', 'Нанатович');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (12, 'Аркадий', 'Стругацкий', 'Нанатович');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (36, 'Marcin', 'Máša ', 'Byrnessi');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (30, 'Alwine', 'Arielle', 'Reeve');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (38, 'Anatoly', 'Anatolle', 'Anatolivich');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (39, 'Some', 'Somich', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (6, 'Даниель', 'Каненман', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (10, 'Evgeniy', 'Petrov', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (25, 'Elda', 'Sidor', 'Vale');
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (40, 'Дина', 'Рубина', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (41, 'Testing', 'Author', NULL);
INSERT INTO public.authors OVERRIDING SYSTEM VALUE VALUES (43, 'Adrim', 'Olsdfsd', NULL);


--
-- TOC entry 3457 (class 0 OID 17263)
-- Dependencies: 216
-- Data for Name: books; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (29, 4, '978-5-34-334479-4', 'The Magic', 'eng', 2015, 1, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (30, 4, '978-5-34-334479-7', 'Diamond', 'eng', 2016, 3, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (37, 11, '9003', 'TEST_BOOK3', 'eng', 2023, 12, 7);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (10, 8, '978-5-389-10956-8', 'One-story America', 'eng', 2018, 7, 9);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (2, 2, '978-0-32-177640-2', 'Язык программирования С++', 'ru', 2020, 1, 5);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (27, 3, '978-5-04-544476-3', 'Black and White', 'eng', 2013, 1, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (40, 5, '900-3', 'New book', 'ru', 2018, 2, 11);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (5, 5, '978-5-96-144015-7', 'Laws of Human Nature', 'eng', 2020, 2, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (11, 8, '978-5-17-112382-6', 'Мертвые души', 'ru', 2023, 3, 9);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (17, 6, '978-5-17-118314-1', 'Sorrow of Satan', 'eng', 2020, 3, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (18, 9, '978-5-6047292-6-7', 'How to read books', 'eng', 2022, 4, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (7, 7, '978-5-04-187850-4', 'Travel to Eleusis', 'eng', 2019, 3, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (4, 4, '978-5-00-117545-2', 'Код', 'ru', 2019, 1, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (3, 3, '978-5-90-668657-2', 'Сила настоящего', 'ru', 2015, 2, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (9, 7, '978-5-04-170250-2', 'Преступление и наказание', 'ru', 2021, 6, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (15, 10, '978-5-389-21444-6', 'Drakula', 'eng', 2022, 3, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (35, 9, '9001', 'T_BOOK2', 'ru', 2021, 8, 4);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (39, 3, '978-0-73-521129-2', 'title', 'ru', 2021, 3, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (19, 10, '978-7-9202-1022-5', 'Vengeance Of Darkness', 'eng', 2021, 4, 9);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (8, 7, '978-5-04-170250-2', 'Братья Карамазовы', 'ru', 2021, 3, 9);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (14, 6, '978-5-17-080086-5', 'Lord of the Flies', 'eng', 2022, 3, 9);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (12, 5, '978-5-17-092159-1', 'Трудно быть богом', 'ru', 2015, 3, 10);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (24, 3, '978-3-09-118316-5', 'Genius', 'eng', 2019, 4, 9);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (16, 10, '978-5-04-116678-6', 'Мастер и маргарита', 'ru', 2022, 3, 8);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (6, 6, '978-5-17-080053-7', 'Думай медленно... Решай быстро', 'ru', 2021, 3, 8);
INSERT INTO public.books OVERRIDING SYSTEM VALUE VALUES (13, 6, '978-5-17-146484-4', 'Идиот', 'ru', 2023, 3, 9);


--
-- TOC entry 3458 (class 0 OID 17266)
-- Dependencies: 217
-- Data for Name: books_authors; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.books_authors VALUES (27, 33);
INSERT INTO public.books_authors VALUES (2, 2);
INSERT INTO public.books_authors VALUES (3, 3);
INSERT INTO public.books_authors VALUES (4, 4);
INSERT INTO public.books_authors VALUES (5, 5);
INSERT INTO public.books_authors VALUES (6, 6);
INSERT INTO public.books_authors VALUES (7, 7);
INSERT INTO public.books_authors VALUES (8, 8);
INSERT INTO public.books_authors VALUES (9, 8);
INSERT INTO public.books_authors VALUES (10, 9);
INSERT INTO public.books_authors VALUES (10, 10);
INSERT INTO public.books_authors VALUES (11, 11);
INSERT INTO public.books_authors VALUES (40, 34);
INSERT INTO public.books_authors VALUES (40, 12);
INSERT INTO public.books_authors VALUES (13, 8);
INSERT INTO public.books_authors VALUES (14, 14);
INSERT INTO public.books_authors VALUES (15, 15);
INSERT INTO public.books_authors VALUES (16, 16);
INSERT INTO public.books_authors VALUES (17, 17);
INSERT INTO public.books_authors VALUES (19, 19);
INSERT INTO public.books_authors VALUES (24, 35);
INSERT INTO public.books_authors VALUES (29, 25);
INSERT INTO public.books_authors VALUES (30, 26);
INSERT INTO public.books_authors VALUES (35, 35);
INSERT INTO public.books_authors VALUES (35, 9);
INSERT INTO public.books_authors VALUES (39, 1);
INSERT INTO public.books_authors VALUES (12, 13);
INSERT INTO public.books_authors VALUES (12, 12);
INSERT INTO public.books_authors VALUES (37, 15);
INSERT INTO public.books_authors VALUES (37, 39);
INSERT INTO public.books_authors VALUES (37, 3);


--
-- TOC entry 3460 (class 0 OID 17270)
-- Dependencies: 219
-- Data for Name: editions; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (2, 'Sofia', 'Russia');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (3, 'Dialectika', 'Russia');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (4, 'Print Corp.', 'Belarus');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (8, 'LOOPS', 'New Zeland');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (11, 'FDMM', 'Nigeria');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (7, 'UUU', 'USA');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (9, 'POPSS', 'USA');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (10, 'RE E.', 'USA');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (12, 'QAZ', 'USA');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (18, 'BEST', 'Russia');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (5, 'ZNN', 'USA');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (6, 'AW', 'USA');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (24, 'PPD', 'Russia');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (1, 'ACT', 'Moldova');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (15, 'VFT', 'RUSSIA');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (19, 'GGWP', NULL);
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (25, 'New Era', NULL);
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (26, 'EKSMO', 'Russia');
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (27, 'TESTING', NULL);
INSERT INTO public.editions OVERRIDING SYSTEM VALUE VALUES (28, 'SOUP', 'Moldova');


--
-- TOC entry 3462 (class 0 OID 17274)
-- Dependencies: 221
-- Data for Name: genres; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (1, 'Computer Literature');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (5, 'Fantasy');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (2, 'Psychology');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (4, 'Scientific Literature');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (6, 'Classic Fiction');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (7, 'Horror Fiction');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (8, 'Short Story');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (9, 'Philosophy');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (10, 'Travel');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (11, 'Romance Fiction');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (3, 'Classic Fiction');
INSERT INTO public.genres OVERRIDING SYSTEM VALUE VALUES (12, 'test1234');


--
-- TOC entry 3464 (class 0 OID 17278)
-- Dependencies: 223
-- Data for Name: librarians; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.librarians OVERRIDING SYSTEM VALUE VALUES (1, 'Admin111', 'Admin111');


--
-- TOC entry 3466 (class 0 OID 17282)
-- Dependencies: 225
-- Data for Name: orders; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (10, 20, 7, '2023-12-17', '2024-03-16', 'Active');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (9, 21, 6, '2023-12-09', '2024-02-29', 'Active');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (13, 7, 2, '2023-12-18', '2024-03-17', 'Active');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (15, 14, 29, '2023-12-18', '2024-03-17', 'Active');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (16, 24, 18, '2023-12-18', '2024-03-17', 'Active');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (12, 20, 11, '2023-12-17', '2023-12-31', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (17, 20, 13, '2023-12-18', '2024-03-17', 'Active');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (18, 20, 19, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (20, 20, 8, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (21, 20, 14, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (22, 26, 2, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (23, 20, 24, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (24, 20, 16, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (25, 20, 6, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (26, 20, 2, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (27, 20, 13, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (28, 20, 37, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (29, 20, 10, '2023-12-19', '2023-12-22', 'Not confirmed');
INSERT INTO public.orders OVERRIDING SYSTEM VALUE VALUES (30, 27, 2, '2023-12-19', '2024-12-30', 'Active');


--
-- TOC entry 3468 (class 0 OID 17286)
-- Dependencies: 227
-- Data for Name: readers; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (6, 'user3', 'Qwerty123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (7, 'user4', 'Qwerty1234', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (9, 'user5', 'Qwerty12345', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (1, 'user1', 'Qwerty123', '+79253551812', 'mail@mail.ru');
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (10, 'qwerty', 'Asd123456', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (15, 'bbbb', 'Bbbb1234', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (16, 'Detrix', 'Qwerty123', '+79253551812', 'Detrix@gmail.com');
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (17, 'Sanya', 'Qwerty123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (18, 'user7', 'Qwerty123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (19, 'user8', 'Qwerty123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (21, 'Olya', 'Qwerty123', '+79254874325', 'stella9494@mail.ru');
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (14, 'aaaa', 'Aaaa1234', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (20, 'Ketrix', 'ZXCzxc123', '+79813441900', NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (22, 'Dan', 'Qwerty123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (23, 'SomeReader', 'Qwerty123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (24, 'SomeReader1', 'ZXCzxc123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (25, 'kett', 'ASDasd123', NULL, NULL);
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (26, 'Vlad', 'Qwerty123', '12345678987', 'bbjbj@gff.gf');
INSERT INTO public.readers OVERRIDING SYSTEM VALUE VALUES (27, 'user111', 'Qwerty123', NULL, NULL);


--
-- TOC entry 3470 (class 0 OID 17290)
-- Dependencies: 229
-- Data for Name: reviews; Type: TABLE DATA; Schema: public; Owner: ketrix
--

INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (3, 1, 14, 5, 'Hmmmmmmm... Interesting story?', '2023-10-24 16:14:26');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (5, 6, 2, 5, 'I Hate Everything About You! Cause I love you!', '2023-10-24 20:30:31');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (24, 26, 2, 5, 'dffgdfgdgdgf', '2023-12-19 14:56:38');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (14, 14, 13, 2, '', '2023-11-25 14:58:34');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (17, 16, 13, 5, '', '2023-11-28 12:48:52');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (18, 17, 2, 5, 'fgghhj', '2023-11-28 15:35:46');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (6, NULL, 4, 5, 'old', '2014-07-11 03:00:00');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (15, 15, 13, 3, 'baka', '2023-11-25 14:59:49');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (16, 16, 2, 5, 'GOOD!!!', '2023-11-28 12:46:00');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (19, 21, 13, 5, 'Fantastic', '2023-12-04 15:33:34');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (21, NULL, 13, 4, NULL, '2023-12-06 18:25:36');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (22, NULL, 13, 3, 'testing!', '2023-12-06 18:25:37');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (25, 20, 24, 1, '', '2023-12-19 15:45:13');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (2, 9, 2, 3, 'Not bad at all. But count of pages...', '2023-10-24 19:55:17');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (13, 7, 2, 1, 'bad', '2023-11-14 12:49:40');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (23, 20, 2, 1, '   n mm  mm m m', '2023-12-19 15:45:47');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (26, 20, 3, 3, '', '2023-12-19 15:45:51');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (27, 20, 13, 1, '', '2023-12-19 15:46:09');
INSERT INTO public.reviews OVERRIDING SYSTEM VALUE VALUES (28, 27, 2, 5, 'ifodgfdg', '2023-12-19 16:50:20');


--
-- TOC entry 3478 (class 0 OID 0)
-- Dependencies: 215
-- Name: authors_author_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.authors_author_id_seq', 43, true);


--
-- TOC entry 3479 (class 0 OID 0)
-- Dependencies: 218
-- Name: books_book_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.books_book_id_seq', 40, true);


--
-- TOC entry 3480 (class 0 OID 0)
-- Dependencies: 220
-- Name: editions_edition_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.editions_edition_id_seq', 28, true);


--
-- TOC entry 3481 (class 0 OID 0)
-- Dependencies: 222
-- Name: genres_genre_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.genres_genre_id_seq', 14, true);


--
-- TOC entry 3482 (class 0 OID 0)
-- Dependencies: 224
-- Name: librarians_librarian_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.librarians_librarian_id_seq', 1, true);


--
-- TOC entry 3483 (class 0 OID 0)
-- Dependencies: 226
-- Name: orders_order_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.orders_order_id_seq', 30, true);


--
-- TOC entry 3484 (class 0 OID 0)
-- Dependencies: 228
-- Name: readers_reader_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.readers_reader_id_seq', 27, true);


--
-- TOC entry 3485 (class 0 OID 0)
-- Dependencies: 230
-- Name: reviews_review_id_seq; Type: SEQUENCE SET; Schema: public; Owner: ketrix
--

SELECT pg_catalog.setval('public.reviews_review_id_seq', 28, true);


--
-- TOC entry 3276 (class 2606 OID 17310)
-- Name: authors authors_unique_snm; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.authors
    ADD CONSTRAINT authors_unique_snm UNIQUE (name, surname, middlename);


--
-- TOC entry 3278 (class 2606 OID 17312)
-- Name: authors pk_authors_author_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.authors
    ADD CONSTRAINT pk_authors_author_id PRIMARY KEY (author_id);


--
-- TOC entry 3280 (class 2606 OID 17314)
-- Name: books pk_books_book_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.books
    ADD CONSTRAINT pk_books_book_id PRIMARY KEY (book_id);


--
-- TOC entry 3282 (class 2606 OID 17316)
-- Name: books_authors pk_books_book_id_authors_author_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.books_authors
    ADD CONSTRAINT pk_books_book_id_authors_author_id PRIMARY KEY (author_id, book_id);


--
-- TOC entry 3284 (class 2606 OID 17318)
-- Name: editions pk_editions_edition_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.editions
    ADD CONSTRAINT pk_editions_edition_id PRIMARY KEY (edition_id);


--
-- TOC entry 3286 (class 2606 OID 17320)
-- Name: genres pk_genres_genre_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.genres
    ADD CONSTRAINT pk_genres_genre_id PRIMARY KEY (genre_id);


--
-- TOC entry 3288 (class 2606 OID 17322)
-- Name: librarians pk_librarians_librarian_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.librarians
    ADD CONSTRAINT pk_librarians_librarian_id PRIMARY KEY (librarian_id);


--
-- TOC entry 3292 (class 2606 OID 17324)
-- Name: orders pk_orders_order_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT pk_orders_order_id PRIMARY KEY (order_id);


--
-- TOC entry 3294 (class 2606 OID 17326)
-- Name: readers pk_readers_reader_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.readers
    ADD CONSTRAINT pk_readers_reader_id PRIMARY KEY (reader_id);


--
-- TOC entry 3298 (class 2606 OID 17328)
-- Name: reviews pk_reviews_review_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.reviews
    ADD CONSTRAINT pk_reviews_review_id PRIMARY KEY (review_id);


--
-- TOC entry 3274 (class 2606 OID 17795)
-- Name: books quantity_not_zero; Type: CHECK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE public.books
    ADD CONSTRAINT quantity_not_zero CHECK ((quantity > 0)) NOT VALID;


--
-- TOC entry 3290 (class 2606 OID 17330)
-- Name: librarians unique_librarian_login; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.librarians
    ADD CONSTRAINT unique_librarian_login UNIQUE (login);


--
-- TOC entry 3296 (class 2606 OID 17332)
-- Name: readers unique_reader_login; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.readers
    ADD CONSTRAINT unique_reader_login UNIQUE (login);


--
-- TOC entry 3300 (class 2606 OID 17835)
-- Name: reviews unique_reviews_reader_id_book_id; Type: CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.reviews
    ADD CONSTRAINT unique_reviews_reader_id_book_id UNIQUE (reader_id, book_id);


--
-- TOC entry 3303 (class 2606 OID 17333)
-- Name: books_authors fk_books_authors_authors; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.books_authors
    ADD CONSTRAINT fk_books_authors_authors FOREIGN KEY (author_id) REFERENCES public.authors(author_id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3304 (class 2606 OID 17338)
-- Name: books_authors fk_books_authors_books; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.books_authors
    ADD CONSTRAINT fk_books_authors_books FOREIGN KEY (book_id) REFERENCES public.books(book_id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3301 (class 2606 OID 17979)
-- Name: books fk_books_editions; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.books
    ADD CONSTRAINT fk_books_editions FOREIGN KEY (edition_id) REFERENCES public.editions(edition_id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3302 (class 2606 OID 17984)
-- Name: books fk_books_genres; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.books
    ADD CONSTRAINT fk_books_genres FOREIGN KEY (genre_id) REFERENCES public.genres(genre_id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3305 (class 2606 OID 17353)
-- Name: orders fk_orders_books; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT fk_orders_books FOREIGN KEY (book_id) REFERENCES public.books(book_id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3306 (class 2606 OID 17358)
-- Name: orders fk_orders_readers; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT fk_orders_readers FOREIGN KEY (reader_id) REFERENCES public.readers(reader_id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3307 (class 2606 OID 17363)
-- Name: reviews fk_reviews_books; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.reviews
    ADD CONSTRAINT fk_reviews_books FOREIGN KEY (book_id) REFERENCES public.books(book_id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3308 (class 2606 OID 17368)
-- Name: reviews fk_reviews_readers; Type: FK CONSTRAINT; Schema: public; Owner: ketrix
--

ALTER TABLE ONLY public.reviews
    ADD CONSTRAINT fk_reviews_readers FOREIGN KEY (reader_id) REFERENCES public.readers(reader_id) ON UPDATE CASCADE ON DELETE SET NULL NOT VALID;


-- Completed on 2023-12-20 14:04:49 MSK

--
-- PostgreSQL database dump complete
--

