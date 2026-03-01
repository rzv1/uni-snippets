-- Sintaxa pentru creare procedura care nu returneaza nimic
CREATE PROCEDURE AdaugaConstrangere
AS
BEGIN
ALTER TABLE Atractii
ADD CONSTRAINT df_varsta_min DEFAULT 12 FOR varsta_min;
END;

-- Apelare procedura creata
EXEC AdaugaConstrangere;

-- Crearea procesurilor trebuie facuta in batch-uri separate
-- deci dupa fiecare procedura creata se pune GO
GO
-- Sintaxa pentru procedura ce returneaza valori si cu parametru de intrare
CREATE PROCEDURE ReturneazaAtractii @varsta_min INT
AS
BEGIN
SELECT * FROM Atractii
WHERE varsta_min = @varsta_min;
END;

-- Se apeleaza cu ReturneazaAtractii 12
GO
-- Putem declara variabile ouput
ALTER PROCEDURE ReturneazaAtractii @varsta_min INT,
@nr_atractii INT OUTPUT
AS
BEGIN
SELECT @nr_atractii = COUNT(*) FROM Atractii WHERE varsta_min = @varsta_min;
END;

-- Declarare variabila
DECLARE @nratractii AS INT;
-- Initializare
SET @nratractii=0;
-- Apelare functie (se scrie OUTPUT obligatoriu)
EXEC ReturneazaAtractii 12,@nr_atractii=@nratractii OUTPUT;
-- Afiseaza variabile
PRINT @nratractii;

-- Generarea mesajelor de eroare folosind RAISERROR
-- RAISERROR ({ msg_id | msg_str | @local_var }, {severity, state})
-- Poate referi mesaj stocat din sys.messages catalog view
-- sau Construieste mesajul dinamic

-- nivelul severity in (0,18)
-- state in (0,255) e un fel de cod de eroare, pentru a diferentia sursele erorii


--Stergere procedura
DROP PROCEDURE ReturneazaAtractii;

-- Variabilele globale fac parte din sistem si nu trebuie declarate tot mereu.
-- Acestea incep cu @@
-- Exemple: @@ERROR, @@IDENTITY, @@ROWCOUNT, @@SERVERNAME, @@SPID, @@VERSION

-- SET NOCOUNT ON - opreste afisarea numarului liniilor afectate dupa fiecare modificare efectuata.
GO
-- EXEC poate fi folosit pentru a executa cod SQL dinamic
CREATE PROCEDURE ReturneazaDate @nume_tabel VARCHAR(100)
AS
BEGIN
EXEC('SELECT * FROM ' + @nume_tabel);
END;
-- Executarea astfel poate ridica probleme de sql injection, astfel ca se prefera
--procedura stocata sp_executesql (accepta doar siruri Unicode).

DECLARE @sql NVARCHAR(100);
SET @sql=N'SELECT nume, descriere FROM Sectiuni WHERE nume<>@nume AND id>@id;';
EXEC sp_executesql @sql, N'@nume VARCHAR(100), @id INT', @nume=N'sectiunea 1', @id=5;

-- TSQL ofera control al fluxului de executie.
-- Se poate folosi RETURN in cadrul unui BEGIN - END.
GO;
CREATE PROCEDURE VerificaVarsta @cod_a INT
AS
BEGIN
IF((SELECT varsta_minima FROM Atractii WHERE cod_a=@cod_a)=12)
	RETURN 1;
ELSE
	RETURN 2;
END;

--Pentru a se verifica valoarea returnata
DECLARE @status INT;
EXEC @status=VerificaVarsta 1;
SELECT 'Status'=@status;

-- Avem WHILE cu BREAK si CONTINUE comportament ca in C.
-- GOTO ca in assembly:
Label:
GOTO Label;
-- WAITFOR intrerupe executia
WAITFOR TIME '22:00'; -- executia incepe la 22:00
WAITFOR DELAY '03:00:00'; -- executia continua peste 3 ore

-- Avem THROW, TRY, CATCH ca in C
THROW 50002, N'Inregistrarea nu exista', 1; -- cod_eroare, mesaj, state
BEGIN TRY

END TRY
BEGIN CATCH

END CATCH

-- In interiorul unui CATCH se pot folosi proceduri care returneaza:
-- ERROR_NUMBER(), ERROR_SEVERITY(), ERROR_STATE(), ERROR_PROCEDURE(), ERROR_LINE(), ERROR_MESSAGE();

-- Exercitii:
-- Adaugare sectiune noua in Sectiuni.
GO;
CREATE PROCEDURE AdaugaSectiune @nume NVARCHAR(100), @descriere NVARCHAR(100)
AS
BEGIN
	INSERT INTO Sectiuni VALUES (@nume, @descriere);
END;
GO
EXEC AdaugaSectiune N'sectiune noua', N'sectiune misto';
SELECT * FROM Sectiuni;

-- Adaugare categorie. Daca exista deja se afiseaza pe ecran mesaj de eroare.
CREATE PROCEDURE AdaugaCategorie @nume NVARCHAR(100)
AS
BEGIN
	IF((SELECT COUNT(*) FROM Categorii WHERE nume = @nume) > 0)
	BEGIN
		PRINT 'Categoria exista deja!';
		RETURN 1;
	END;
	ELSE
		INSERT INTO Categorii VALUES (@nume);
END;
GO
DECLARE @status INT
EXEC @status=AdaugaCategorie N'Avram'
SELECT @status
SELECT * FROM Categorii;

-- Procedura care creeaza atractie noua. Daca sectiunea nu exista deja se adauga si ea.
CREATE PROCEDURE AdaugaAtractie @nume NVARCHAR(100), @descriere NVARCHAR(100), @varsta_minima INT, @sectiune NVARCHAR(100)
AS
BEGIN
	IF((SELECT COUNT(*) FROM Sectiuni WHERE nume = @sectiune) = 0)
		INSERT INTO Sectiuni (nume) VALUES (@sectiune);
	DECLARE @id INT
	SET @id=(SELECT id FROM Sectiuni WHERE nume=@sectiune);
	INSERT INTO Atractii VALUES (@nume, @descriere, @varsta_minima, @id);
END;
GO
EXEC AdaugaAtractie N'Atr1', N'Atr1 desc', 12, N'Sectiunea noua';
SELECT * FROM Sectiuni;
SELECT * FROM Atractii;

-- Procedura care gaseste Vizitatorul cu o anume adresa
CREATE PROCEDURE GasesteVizitator @adresa NVARCHAR(100), @id INT OUTPUT
AS
BEGIN
	IF((SELECT COUNT(*) FROM Vizitatori WHERE adresa = @adresa) > 0)
		SET @id = (SELECT id FROM Vizitatori WHERE adresa = @adresa);
	ELSE
		THROW 50002, N'Vizitatorul nu exista! ', 1;
END;
GO
DECLARE @id INT = 0;
BEGIN TRY
	EXEC GasesteVizitator N'e.com', @id OUTPUT;
	PRINT 'Id-ul vizitatorului este: ';
	PRINT @id;
END TRY
BEGIN CATCH
	PRINT 'A aparut eroarea:';
	PRINT ERROR_MESSAGE();
END CATCH;

-- Procedura pentru adaugare nota cu erori daca se introduc date gresite
CREATE PROCEDURE AdaugaNota @vizitator INT, @atractie INT, @nota INT
AS
BEGIN
	IF((SELECT COUNT(*) FROM Atractii WHERE id = @atractie) = 0 OR
	(SELECT COUNT(*) FROM Vizitatori WHERE id = @vizitator) = 0)
		THROW 50002, N'Unul din id-uri nu e bun', 1;
	IF(@nota < 1 OR @nota > 10)
		THROW 50003, N'Nota nu e buna', 1;
	INSERT INTO Vizite VALUES (@vizitator, @atractie, @nota);
END;
GO
BEGIN TRY
	EXEC AdaugaNota 3, 7, 8;
END TRY
BEGIN CATCH
	PRINT 'A aparut o eroare:'
	PRINT ERROR_MESSAGE();
END CATCH
SELECT * FROM Vizite;

-- Actualizeaza adresa unui vizitator
CREATE PROCEDURE ActualizareAdresa @id INT, @adresa NVARCHAR(100)
AS
BEGIN
	IF((SELECT COUNT(*) FROM Vizitatori WHERE id = @id) = 0)
		THROW 50005, N'Vizitatorul nu exista', 1;
	UPDATE Vizitatori SET adresa=@adresa WHERE id=@id;
END;
GO
BEGIN TRY
	EXEC ActualizareAdresa 2, N'l.com';
END TRY
BEGIN CATCH
	PRINT ERROR_MESSAGE();
END CATCH
SELECT * FROM Vizitatori;

CREATE PROCEDURE GetVizitatori
AS
BEGIN
	SELECT nume, adresa, nr_note=COUNT(*) FROM Vizite
	JOIN Vizitatori ON idVizitator = id
	GROUP BY nume, adresa
END;
GO
EXEC GetVizitatori;

CREATE PROCEDURE StergeAtractie @nume NVARCHAR(100)
AS
BEGIN
	IF((SELECT COUNT(*) FROM Vizite JOIN Atractii ON idAtractie = id WHERE nume=@nume) > 0)
		THROW 50010, N'Atractia are note', 1;
	DELETE FROM Atractii WHERE nume=@nume;
END;
GO

EXEC StergeAtractie N'rollermonster';
SELECT * FROM Atractii;