PRAGMA foregin_keys = ON;

-- Create schemas
-- Create tables
CREATE TABLE Zamowienie
(
    id_zamowienia INTEGER NOT NULL,
    id_klienta INTEGER NOT NULL,
    data DATE NOT NULL,
    CONSTRAINT zamowienie_pk PRIMARY KEY(id_zamowienia)
);
CREATE TABLE ZamowionaPizza
(
    id_zamowionej int NOT NULL,
    id_podstawy INTEGER NOT NULL,
    id_rozmiaru INTEGER NOT NULL,
    id_zamowienia INTEGER NOT NULL,
    CONSTRAINT zamowionapizza_pk PRIMARY KEY
    (id_zamowionej)
);
CREATE TABLE Skladnik
(
    id_skladnika INTEGER NOT NULL ,
    nazwa_skladnika VARCHAR(20),
    cena_domyslna DOUBLE PRECISION NOT NULL,
    CONSTRAINT skladnik_pk PRIMARY KEY(id_skladnika)
);
CREATE TABLE Klient
(
    id_klienta INTEGER NOT NULL,
    imie VARCHAR(20) NOT NULL,
    nazwisko VARCHAR(50) NOT NULL,
    email VARCHAR(200) NOT NULL,
    ulica VARCHAR(60) NOT NULL,
    miasto VARCHAR(60) NOT NULL,
    telefon INTEGER NOT NULL,
    CONSTRAINT klient_pk PRIMARY KEY(id_klienta)
);
CREATE TABLE PodstawaDoPizzy
(
    id_podstawy INTEGER NOT NULL,
    nazwa VARCHAR(40) NOT NULL,
    cena_podstawy DOUBLE PRECISION NOT NULL,
    CONSTRAINT podstawadopizzy_pk PRIMARY KEY(id_podstawy)
);
CREATE TABLE Rozmiar
(
    id_rozmiaru INTEGER NOT NULL,
    nazwa_rozmiaru INTEGER NOT NULL,
    srednica INTEGER NOT NULL,
    mnoznik_ceny INTEGER NOT NULL,
    CONSTRAINT rozmiar_pk PRIMARY KEY(id_rozmiaru)
);
CREATE TABLE DodatkoweSkladniki
(
    id_zamowionej INTEGER NOT NULL,
    id_skladnika INTEGER NOT NULL,
    CONSTRAINT dodatkoweskladniki_pk PRIMARY KEY(id_zamowionej)
);
CREATE TABLE SkladnikiPodstawy
(
    id_podstawy INTEGER NOT NULL,
    id_skladnika INTEGER NOT NULL,
    CONSTRAINT skladnikipodstawy_pk PRIMARY KEY(id_podstawy, id_skladnika)
);
-- Create FKs
-- ALTER TABLE Zamowienie
--     ADD FOREIGN KEY (id_klienta)
--     REFERENCES Klient(id_klienta)
-- ;
-- ALTER TABLE ZamowionaPizza
--     ADD FOREIGN KEY (id_rozmiaru)
--     REFERENCES Rozmiar(id_rozmiaru)
-- ;
-- ALTER TABLE ZamowionaPizza
--     ADD FOREIGN KEY (id_podstawy)
--     REFERENCES PodstawaDoPizzy(id_podstawy)
-- ;
-- ALTER TABLE DodatkoweSkladniki
--     ADD FOREIGN KEY (id_zamowionej)
--     REFERENCES ZamowionaPizza(id_zamowionej)
-- ;
-- ALTER TABLE DodatkoweSkladniki
--     ADD FOREIGN KEY (id_skladnika)
--     REFERENCES Skladnik(id_skladnika)
-- ;
-- ALTER TABLE ZamowionaPizza
--     ADD FOREIGN KEY (id_zamowienia)
--     REFERENCES Zamowienie(id_zamowienia)
-- ;
-- ALTER TABLE SkladnikiPodstawy
--     ADD FOREIGN KEY (id_podstawy)
--     REFERENCES PodstawaDoPizzy(id_podstawy)
-- ;
-- ALTER TABLE SkladnikiPodstawy
--     ADD FOREIGN KEY (id_skladnika)
--     REFERENCES Skladnik(id_skladnika)
-- ;
-- Data
INSERT INTO Skladnik
    (nazwa_skladnika, cena_domyslna)
VALUES
    ('Szynka', 1.0),
    ('Salami', 2.0),
    ('Pomidor', 3.0);
INSERT INTO PodstawaDoPizzy
    (nazwa, cena_podstawy)
VALUES
    ('Margherita', 17),
    ('Hawajska', 23),
    ('Kebab', 24);
INSERT INTO Rozmiar
    (nazwa_rozmiaru, srednica, mnoznik_ceny)
VALUES
    ("Malutenka", 14, 0.5 ),
    ("Ogromna", 41, 3),
    ("Normalna", 24, 1);

INSERT INTO Klient 
    (imie, nazwisko, email, ulica, miasto, telefon)
VALUES
    ("Arek", "Dyrdymałek", "ad@mimuw.edu.pl", "Banacha 1", "Warszawa", "123456789"),
    ("Asia", "Dyrdymałek", "ad2@mimuw.edu.pl", "Banacha 2", "Warszawa", "191231289"),
    ("Kamil", "Dyrdymałek", "kd@mimuw.edu.pl", "Banacha 3", "Warszawa", "114123789")
;

CREATE TRIGGER tr_unique_client BEFORE INSERT ON Klient 
FOR EACH ROW
BEGIN
SELECT RAISE(FAIL, "Duplicate") FROM Klient WHERE imie = NEW.imie AND nazwisko=NEW.nazwisko AND telefon = NEW.telefon;
END;

   

-- Cena zamowienia
-- PROCEDURE cena_zamowienia(id_zamowienia IN INTEGER)
-- RETURN INTEGER
-- IS
--     res INTEGER;
--     res2 INTEGER;
-- BEGIN
--     SELECT (SUM(cena_domyslna * rozmiar)) INTO res
--     FROM ZamowionaPizza zp JOIN Skladnik sk JOIN Rozmiar roz
--     WHERE id_zamowienia = zp.id_zamowienia;

--     SELECT(SUM(cena_podstawy * mnoznik_ceny)) INTO res2
--     FROM ZamowionaPizza zp JOIN Rozmiar roz JOIN PodstawaDoPizzy
--     WHERE id_zamowienia = zp.id_zamowienia;

--     RETURN res + res2;
-- END;

-- Remove zamowienie