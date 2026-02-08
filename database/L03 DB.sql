--Scrieţi un script SQL care va:
--- modifica tipul unei coloane;
--- adauga o costrângere de “valoare implicită” pentru un câmp;
--- creea/şterge o tabelă;
--- adăuga un câmp nou;
--- creea/şterge o constrângere de cheie străină.

CREATE TABLE VersiuneCurenta (
	versiune INT
);

CREATE TABLE Versiune (
	versiune INT PRIMARY KEY,
	update_proc NVARCHAR(100),
	rollback_proc NVARCHAR(100)
);

INSERT INTO Versiune VALUES
(1, 'Update_V1_to_V2', ''),
(2, 'Update_V2_to_V3', 'Rollback_V2_to_V1'),
(3, 'Update_V3_to_V4', 'Rollback_V3_to_V2'),
(4, 'Update_V4_to_V5', 'Rollback_V4_to_V3'),
(5, 'Update_V5_to_V6', 'Rollback_V5_to_V4'),
(6, '', 'Rollback_V6_to_V5');
GO
-- Modifica tipul unei coloane
CREATE OR ALTER PROCEDURE Update_V1_to_V2
AS
	ALTER TABLE Clienti
	ALTER COLUMN email VARCHAR(100);

GO

CREATE OR ALTER PROCEDURE Rollback_V2_to_V1
AS
BEGIN
	ALTER TABLE Clienti
	ALTER COLUMN email VARCHAR(36);
END;
GO

-- Adauga constrangere DEFAULT
CREATE OR ALTER PROCEDURE Update_V2_to_V3
AS
BEGIN
	ALTER TABLE Plati
	ADD CONSTRAINT cMetodaPlata DEFAULT 'card' FOR metodaPlata;
END;
GO

CREATE OR ALTER PROCEDURE Rollback_V3_to_V2
AS
BEGIN
	ALTER TABLE Plati
	DROP CONSTRAINT cMetodaPlata;
END;
GO

-- Creare tabela
CREATE OR ALTER PROCEDURE Update_V3_to_V4
AS
BEGIN
	CREATE TABLE tabela(
		id INT PRIMARY KEY IDENTITY,
		ceva VARCHAR(100)
	);
END;
GO

CREATE OR ALTER PROCEDURE Rollback_V4_to_V3
AS
BEGIN
	DROP TABLE dbo.tabela;
END;
GO

-- Adauga camp nou
CREATE OR ALTER PROCEDURE Update_V4_to_V5
AS
BEGIN
	ALTER TABLE Clienti
	ADD varsta INT;
END;
GO

CREATE OR ALTER PROCEDURE Rollback_V5_to_V4
AS
BEGIN
	ALTER TABLE Clienti
	DROP COLUMN varsta;
END;
GO

-- Modifica constrangere cheie straina
CREATE OR ALTER PROCEDURE Update_V5_to_V6
AS
BEGIN
	ALTER TABLE Angajati
	DROP CONSTRAINT IF EXISTS FK_Angajati_idSala_5165187F;

	ALTER TABLE Angajati
	ADD CONSTRAINT FK_Angajati_idSala_5165187F FOREIGN KEY (idSala) REFERENCES Sali(id) ON DELETE CASCADE;
END;
GO

CREATE OR ALTER PROCEDURE Rollback_V6_to_V5
AS
BEGIN
	ALTER TABLE Angajati
	DROP CONSTRAINT IF EXISTS FK_Angajati_idSala_5165187F;

	ALTER TABLE Angajati
	ADD CONSTRAINT FK_Angajati_idSala_5165187F FOREIGN KEY (idSala) REFERENCES Sali(id);
END;
GO

-- Declararile nu se fac in bucle
CREATE OR ALTER PROCEDURE SchimbaVersiune @versiune_tinta INT
AS
BEGIN
	DECLARE @versiune_curenta INT;
	DECLARE @proc NVARCHAR(100);
	DECLARE @rproc NVARCHAR(100);
	SET @versiune_curenta = (SELECT versiune FROM VersiuneCurenta);

	IF @versiune_tinta > 6 OR @versiune_tinta < 1 THROW 50002, N'Nu exista versiunea', 1

	IF (@versiune_curenta < @versiune_tinta)
		WHILE (@versiune_curenta < @versiune_tinta)
		BEGIN
			SET @proc = (SELECT update_proc FROM Versiune WHERE versiune = @versiune_curenta);
			EXEC (N'EXEC ' + @proc);
			UPDATE VersiuneCurenta SET versiune = @versiune_curenta + 1;
			SET @versiune_curenta = (SELECT versiune FROM VersiuneCurenta);
		END;
	ELSE IF (@versiune_curenta > @versiune_tinta)
		WHILE (@versiune_curenta > @versiune_tinta)
		BEGIN
			SET @rproc = (SELECT rollback_proc FROM Versiune WHERE versiune = @versiune_curenta);
			EXEC (N'EXEC ' + @rproc);
			UPDATE VersiuneCurenta SET versiune = @versiune_curenta - 1;
			SET @versiune_curenta = (SELECT versiune FROM VersiuneCurenta);
		END;
END;
GO
INSERT INTO VersiuneCurenta VALUES (1)
SELECT * FROM VersiuneCurenta
EXEC SchimbaVersiune 4
