CREATE DATABASE salaFitness;
GO

USE salaFitness;
GO

CREATE TABLE Clienti(
idClienti INT PRIMARY KEY IDENTITY,
nume NVARCHAR(32) NOT NULL,
prenume NVARCHAR(64) NOT NULL
);

CREATE TABLE Abonamente (
    idAbonament INT PRIMARY KEY IDENTITY,
	idBeneficiu INT FOREIGN KEY REFERENCES Beneficii(idBeneficiu),
    denumire NVARCHAR(64) NOT NULL
);

CREATE TABLE Beneficii (
	idBeneficiu INT PRIMARY KEY IDENTITY,
	descriere VARCHAR(128),
	idSala INT FOREIGN KEY REFERENCES Sali(idSala)
);

CREATE TABLE Sali (
	idSala INT PRIMARY KEY IDENTITY,
	numar INT NOT NULL,
	locatie VARCHAR(128) NOT NULL,
);

CREATE TABLE Aparate_Sali (
	idAparat INT FOREIGN KEY REFERENCES Aparate(idAparat),
	idSala INT FOREIGN KEY REFERENCES Sali(idSala),
	id PRIMARY KEY (idAparat, idSala)
);

CREATE TABLE ClientiAbonamente(
idClienti INT FOREIGN KEY REFERENCES Clienti(idClienti),
idAbonament INT FOREIGN KEY REFERENCES Abonamente(idAbonament),
relatie PRIMARY KEY (idClienti, idAbonament)
);

CREATE TABLE Plati (
idPlata INT NOT NULL IDENTITY,
suma INT NOT NULL,
descriere VARCHAR(128) NOT NULL DEFAULT 'Plata',
denumireBanca VARCHAR(128) NOT NULL,
idClienti INT NOT NULL FOREIGN KEY REFERENCES Clienti(idClienti)
);

CREATE TABLE Antrenori (
idClienti INT FOREIGN KEY REFERENCES Clienti(idClienti),
specializare NVARCHAR(128) NOT NULL,
experienta INT NOT NULL,
PRIMARY KEY (idClienti)
);

CREATE TABLE Aparate (
idAparat INT PRIMARY KEY IDENTITY,
cantitate INT NOT NULL DEFAULT 1,
descriere VARCHAR(128)
);

CREATE TABLE Intrari (
idIntrare INT PRIMARY KEY IDENTITY,
dataIntrare DATE NOT NULL DEFAULT GETDATE(),
idClienti INT FOREIGN KEY REFERENCES Clienti(idClienti)
);

CREATE TABLE ClaseFitness (
    idClasa INT PRIMARY KEY IDENTITY,
    denumire NVARCHAR(64) NOT NULL,
    durata INT NOT NULL, -- minute
    dificultate NVARCHAR(32),
    idAntrenor INT FOREIGN KEY REFERENCES Antrenori(idClienti)
);

CREATE TABLE ParticipariClase (
    idClienti INT FOREIGN KEY REFERENCES Clienti(idClienti),
    idClasa INT FOREIGN KEY REFERENCES ClaseFitness(idClasa),
    dataParticipare DATE NOT NULL DEFAULT GETDATE(),
    PRIMARY KEY (idClienti, idClasa),
);

CREATE TABLE IntretinereAparate (
    idIntretinere INT PRIMARY KEY IDENTITY,
    idAparat INT FOREIGN KEY REFERENCES Aparate(idAparat),
    dataRevizie DATE NOT NULL DEFAULT GETDATE(),
    descriere NVARCHAR(256),
);
