CREATE DATABASE Parc;
Go
USE Parc;
Go

CREATE TABLE Categorii(
	id INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(120)
);

CREATE TABLE Vizitatori(
	id INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(120),
	adresa NVARCHAR(120),
	categorie INT FOREIGN KEY REFERENCES Categorii(id)
);

CREATE TABLE Sectiuni(
	id INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(120),
	descriere NVARCHAR(120)
);

CREATE TABLE Atractii(
	id INT PRIMARY KEY IDENTITY,
	nume NVARCHAR(120),
	descriere NVARCHAR(120),
	varsta_minima INT,
	sectiune INT FOREIGN KEY REFERENCES Sectiuni(id)
);

CREATE TABLE Vizite(
	idVizitator INT FOREIGN KEY REFERENCES Vizitatori(id),
	idAtractie INT FOREIGN KEY REFERENCES Atractii(id),
	CONSTRAINT id PRIMARY KEY (idVizitator, idAtractie),
	nota REAL CHECK (nota BETWEEN 1 and 10)
);

INSERT INTO Sectiuni (nume, descriere) VALUES
( 'sectiunea 1', 'cea mai mare sectiune');
INSERT INTO Sectiuni (nume, descriere) VALUES
( 'sectiunea 2', 'cea mai mare sectiune');
INSERT INTO Sectiuni (nume, descriere) VALUES
( 'sectiunea 3', 'cea mai mare sectiune');
INSERT INTO Sectiuni (nume, descriere) VALUES
( 'sectiunea 4', 'cea mai mare sectiune');
INSERT INTO Sectiuni (nume, descriere) VALUES
( 'sectiunea 5', 'cea mai mare sectiune');
INSERT INTO Sectiuni (nume, descriere) VALUES
( 'sectiunea 6', 'cea mai mare sectiune');
INSERT INTO Sectiuni (nume, descriere) VALUES
( 'sectiunea 7', 'cea mai mare sectiune');

INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollercoaster', 'cel mai rapid din parc', 12, 1);
INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollermonster', 'cel mai rapid din parc', 12, 1);
INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollerghoaster', 'cel mai rapid din parc', 12, 1);
INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollerbillster', 'cel mai rapid din parc', 12, 1);
INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollercaster', 'cel mai rapid din parc', 12, 1);
INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollerminister', 'cel mai rapid din parc', 12, 1);
INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollerballster', 'cel mai rapid din parc', 12, 1);
INSERT INTO Atractii (nume, descriere, varsta_minima, sectiune) VALUES
( 'rollerballster', 'cel mai rapid din parc', 12, NULL);


SELECT * FROM Sectiuni;

INSERT INTO Categorii (nume) VALUES ( 'Rookie' ), ( 'Brokie'), ( 'Mid' ), ( 'Upper-Mid' ), ( 'IP' ), ( 'VIP' ), ( 'founder' );

SELECT * FROM Categorii;

INSERT INTO Vizitatori VALUES ('Scorti', 'a.com', 1), ('Bufny', 'b.com', 3), ('Bobby', 'c.com', 6), ('Stronto', 'd.com', 7), ('Bogdi', 'e.com', 4), ('Rusu', 'f.com', 3), ('Cornea', 'g.com', 5);

INSERT INTO Vizite VALUES (1,2,3), (2,3,4), (3,4,5), (4,5,6), (5,6,7), (6,7,7), (1,1,1)

UPDATE Atractii SET descriere='noua descriere'
WHERE descriere='cel mai rapid din parc'

DELETE FROM Atractii WHERE nume='rollerballster';

SELECT * FROM Vizite;

DELETE FROM Vizite WHERE nota=5;

SELECT idVizitator, nota FROM Vizite;

SELECT DISTINCT varsta_minima FROM Atractii;

SELECT nume, varsta_minima FROM Atractii WHERE nume<>'rollercoaster';

--Incepe cu A
-- LIKE 'A%';

--Se termina cu a
-- LIKE '%a';

--Contine un cunvat
-- LIKE '%ana%';

--Contine 3 caractere si se termina cu 'na'
-- LIKE '_na';

-- _ inlocuieste un singur caracter; % inlocuieste 0+

-- LIKE '[ABC]%'
-- LIKE '[^ABC]%'

-- WHERE email is NULL
-- WHERE email is NOT NULL

-- UPDATE Table SET Atribute = "new_value"
-- WHERE Atribute = something

-- DELETE FROM Table 
-- WHERE Atribute = "value";

-- Rezultatul interogarii SELECT este afisat intr-un table rezultat (result-set).

-- SELECT * FROM Table WHERE Atribute [NOT] IN (list, of, values);

-- SQL regex-wannabe: % echivaleaza zero sau mai multe caractere
-- _ echivalent un singur caracter
-- [ce este intre paranteze] echivaleaza cu un singur caracter

-- SELECT * FROM Categorii WHERE nume IN ("pensionari", "copii");
-- SELECT * FROM Sectiuni WHERE nume = "C%"
-- SELECT * FROM Sectiuni WHERE nume = "%_n"

-- Setare alias:
-- Table t
-- Atribute a
-- Atribute AS a
-- a = Atribute

-- COUNT, SUM, MIN, MAX = functii de agregare

-- SELECT C.nume, COUNT(cod_v) nr_vizitatori FROM Categorii C INNER JOIN
-- Vizitatori V ON C.cod_c=V.cod_c GROUP BY C.cod_c, C.nume;
-- ! SELECT obliga ca dupa group by sa apara toate atributele care nu iau parte in functii de agregare
-- SELECT cere C.nume, iar SQL nu permite să selectezi o coloană care nu este nici agregată, nici în GROUP BY.
-- Prefixarea pentru provenienta atributului nu este necesara daca situatia nu este ambigua.

-- EXISTS() returneaza true daca intre paranteze exista cel putin o inregistrare.
-- INNER JOIN se poate rescrie folosind EXISTS:

-- SELECT DISTINCT C.nume FROM Categorii C INNER JOIN Vizitatori V ON C.cod_c = V.cod_c

-- SELECT DISTINCT C.nume FROM Categorii C 
-- WHERE EXISTS(SELECT * FROM Vizitatori v WHERE v.cod_c = C.cod_c)

-- SELECT nume FROM Categorii C WHERE C.cod_c NOT IN (SELECT cod_c FROM Vizitatori v WHERE v.cod_c IS NOT NULL);
-- SELECT C.nume FROM Categorii C WHERE NOT EXISTS(SELECT * FROM Vizitatori V WHERE V.cod_c = C.cod_c)

-- Afisati vizitatorii care nu au dat nicio nota niciunei atractii.
SELECT * FROM Vizitatori V LEFT JOIN Vizite N ON V.id = N.idVizitator;
SELECT * FROM Vizitatori V INNER JOIN Vizite N ON id = idVizitator GROUP BY nume HAVING COUNT(nota) = 0;

-- Afisati numele vizitator, nota si numele atractie vizitate
-- SELECT atribute FROM Table1, Table2 este sintaxa veche de JOIN intre Table1 si Table2.
SELECT V.nume AS Nume_vizitator, nota,  A.nume AS Nume_atractie FROM Vizite
INNER JOIN Vizitatori V ON V.id = idVizitator
INNER JOIN Atractii A ON A.id = idAtractie;

-- Afisati numele vizitatorilor si cate note au dat fiecare
SELECT V.nume, COUNT(nota) AS numar_note FROM Vizite N
FULL JOIN Vizitatori V ON V.id = idVizitator GROUP BY V.nume;

-- Afisati valorile distincte ale notelor date atractiilor
SELECT DISTINCT nota FROM Vizite N

-- Operatorul ANY poate fi folosit si cu <, >, !=;
-- In cazul operatorului =, ANY este echivalent cu IN.

-- Cand compar un atribut cu o multime de alte atribute trebuie sa folosesc mnemonice speciale precum ALL, ANY, IN, NOT IN, etc
-- altfel query-ul nu va compila daca fac egalitate directa.

-- Scrieți o interogare care afișează numele secțiunii, numele și descrierea
-- atracțiilor pentru toate secțiunile care au cel puțin o atracție asociată (se
-- vor include și atracțiile care nu au o secțiune asociată)
SELECT S.nume AS nume_sectiune, A.nume AS nume_atractie, A.descriere FROM Sectiuni S
RIGHT JOIN Atractii A ON S.id = A.sectiune;

-- Scrieți o interogare care afișează numele și vârsta minimă recomandată a
-- atracției și numărul de note primite pentru toate atracțiile care au primit
-- cel puțin 2 note
SELECT A.nume AS nume_atractie, varsta_minima, COUNT(nota) FROM Atractii A
LEFT JOIN Vizite V ON V.idAtractie = id
GROUP BY A.nume, varsta_minima
HAVING COUNT(nota) >= 2;

-- Scrieți o interogare care afișează numele categoriei, numele vizitatorului,
-- nota, numele și descrierea atracției pentru toate categoriile care au
-- numele diferit de ‘adult’ și au vizitatori asociați care au dat cel puțin o notă
-- unei atracții 
SELECT C.nume AS nume_categorie, V.nume, N.nota, A.nume, A.descriere FROM Vizitatori V
INNER JOIN Vizite N ON N.idVizitator = V.id
INNER JOIN Atractii A ON N.idAtractie = A.id
INNER JOIN Categorii C ON C.id = V.categorie
WHERE C.nume <> 'adult' AND V.id IN (SELECT idVizitator FROM Vizite WHERE nota is NOT NULL);

-- Folosind query1 EXCEPT query2, toate elemente din query2 care se regasesc in query1 sunt excluse.
-- UNION [ALL] ; daca punem ALL se iau si duplicatele, fara ALL se face reuniune pe multimi si raman elemente distincte.
-- UNION, INTERCEPT, EXCEPT sunt folosite doar pe interogari care scot exact aceleasi coloane, contrar JOIN-ului care
-- mareste tabelul cu coloane noi.

-- Scrieți o interogare care afișează nota maximă primită de către fiecare
-- atracție și numele atracției (se vor selecta doar acele atracții care au primit
-- cel puțin o notă)
SELECT A.nume, MAX(nota) FROM Atractii A
JOIN Vizite ON idAtractie = id
GROUP BY A.nume;

-- Scrieți o interogare care afișează nota minimă primită de către fiecare
-- atracție și numele atracției (se vor selecta doar acele atracții care au primit
-- cel puțin o notă)
SELECT A.nume, MIN(nota) FROM Atractii A
JOIN Vizite ON idAtractie = id
GROUP BY A.nume;

-- Scrieți o interogare care afișează numele și adresa de email a vizitatorilor
-- care nu aparțin niciunei categorii
SELECT nume, adresa FROM Vizitatori WHERE categorie is null;

-- Scrieți o interogare care afișează numele și descrierea atracțiilor care
-- aparțin unei categorii (valoarea codului de categorie să fie diferită de
-- NULL)
SELECT nume, descriere FROM Atractii WHERE sectiune is not null;