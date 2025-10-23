
-- Cati clienti au mai mult de 1 abonament activ la categoria de forta
SELECT c.id, c.nume
FROM Clienti c WHERE id IN ( 
	SELECT ca.idClienti
	FROM Clienti_Abonamente ca
	WHERE ca.idAbonament IN (
		SELECT a.idAbonament FROM Abonamente a WHERE a.stare = 'activ')
	GROUP BY ca.idClienti
	HAVING COUNT(*) > 1);

SELECT c.id, c.nume, nr_abon = COUNT(ca.idAbonament)
FROM Clienti c
JOIN Clienti_Abonamente ca ON ca.idClienti = c.id
JOIN Abonamente a ON a.idAbonament = ca.idAbonament
WHERE a.denumire = 'standard'
GROUP BY c.id, c.nume
HAVING COUNT(*) > 1;

-- Cati clienti sunt inscrisi la mai mult de 1 clasa de yoga
SELECT c.id, c.nume, nr = COUNT(cc.idClasa)
FROM Clienti c
JOIN Clienti_Clase cc ON cc.idClienti = c.id
JOIN ClaseFitness cf ON cf.idClasa = cc.idClasa
WHERE cf.denumire = 'yoga'
GROUP BY c.id, c.nume
HAVING COUNT(*) > 1;


-- Cati angajati si aparate are fiecare sala
SELECT s.idSala, s.numar, nr_angajati = COUNT(e.idAngajat), nr_aparate = COUNT(DISTINCT a.idAparat)
FROM Sali s
JOIN Aparate a ON a.idSala = s.idSala
JOIN Angajati e ON e.idSala = s.idSala
GROUP BY s.idSala, s.numar;

-- Cate aparate sunt scadente pentru revizie aceasta luna in functie de sala
SELECT s.idSala, s.adresa, nr_aparate = COUNT(DISTINCT a.idAparat)
FROM Sali s
JOIN Aparate a ON a.idSala = s.idSala
JOIN Revizii r ON r.idAparat = a.idAparat
WHERE CURRENT_DATE >= r.dataRevizie + r.perioada
GROUP BY s.idSala, s.numar;

-- Ce aparate sunt scadente pentru revizie in sala X
