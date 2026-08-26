# Raport de Analiza: Concurenta, Izolare si Performanta in Sisteme de Baze de Date (MySQL)

## 1. Introducere
Acest raport analizeaza implementarea unui sistem de testare a tranzactiilor SQL utilizand limbajul Java si driverul JDBC pentru MySQL. Analiza se concentreaza pe trei piloni principali: anomaliile de concurenta la diferite niveluri de izolare, gestionarea blocajelor de tip Deadlock si optimizarea insertiilor masive prin procesare in loturi (Batch Processing).

---

## 2. Analiza Anomaliilor de Concurenta
Sistemul implementat permite simularea scenariilor in care doua fire de executie (Thread-uri) acceseaza simultan aceleasi date. Rezultatele variaza in functie de nivelul de izolare setat.

### 2.1. Dirty Read (Citirea "Murdara")
* **Definitie:** Apare cand o tranzactie citeste date modificate de o alta tranzactie care nu a efectuat inca `COMMIT`.
* **Observatii in cod:** In metoda `runDirtyRead`, Thread-ul A modifica un nume si asteapta, in timp ce Thread-ul B incearca sa il citeasca.
* **Comportament MySQL:** * La `READ_UNCOMMITTED`: Thread-ul B vede valoarea modificata ("Alice"). Daca Thread-ul A face `ROLLBACK`, datele citite de B sunt invalide.
    * La `READ_COMMITTED`: MySQL foloseste un mecanism de *snapshot* care impiedica Thread-ul B sa vada modificarea pana cand A nu confirma tranzactia.

### 2.2. Non-Repeatable Read (Citirea Nerepetabila)
* **Definitie:** O tranzactie citeste acelasi rand de doua ori, dar obtine valori diferite deoarece o alta tranzactie a modificat si comis datele intre cele doua citiri.
* **Observatii in cod:** In `runNonRepeatableRead`, Thread-ul A realizeaza doua selecturi identice separate de o pauza in care Thread-ul B face `UPDATE` si `COMMIT`.
* **Rezultat:** La nivelul `READ_COMMITTED`, anomalia este vizibila. La nivelul `REPEATABLE_READ` (default in MySQL), anomalia este eliminata prin tehnologia MVCC (Multi-Version Concurrency Control).

### 2.3. Phantom Read (Citirea Fantoma)
* **Definitie:** Apare cand un set de randuri care satisfac o conditie se schimba (apar randuri noi) intre doua citiri in aceeasi tranzactie.
* **Impact:** In MySQL, nivelul `REPEATABLE_READ` este mai robust decat standardul SQL teoretic, utilizand *Next-Key Locking* pentru a preveni insertiile in intervalele citite, eliminand astfel majoritatea scenariilor de Phantom Read.

---

## 3. Gestiunea Conflictelor: Deadlock
Blocajul de tip Deadlock reprezinta o situatie in care doua procese se asteapta reciproc la infinit.

### 3.1. Detectia si Prevenirea
* **Scenariul de esec:** Metoda `runDeadLock` demonstreaza cum Thread-ul A blocheaza ID 1 si cere ID 2, in timp ce Thread-ul B blocheaza ID 2 si cere ID 1. MySQL detecteaza acest ciclu si opreste forta una dintre tranzactii pentru a debloca sistemul.
* **Solutia implementata:** Codul demonstreaza ca **ordonarea riguroasa a resurselor** (ambele thread-uri cer ID-urile in aceeasi ordine: 1 apoi 2) elimina complet posibilitatea de Deadlock, deoarece al doilea thread va astepta la prima resursa pana cand primul thread elibereaza intreg lantul de lock-uri.

---

## 4. Analiza Performantei: Batch Processing
Testele de performanta au comparat trei metode de insertie a 5000 de inregistrari, evidentiind diferente masive in timpul de executie.

### 4.1. Rezultate Comparative (Estimari bazate pe logica codului)
| Metoda | Mecanism | Eficienta | Impact Disk/Retea |
| :--- | :--- | :--- | :--- |
| **Auto-commit (Individual)** | 5000 de tranzactii separate | Foarte Scazuta | Extrem de mare (flush la fiecare rand) |
| **Batch Many (100)** | 50 de loturi de cate 100 | Inalta | Redus (mai putine pachete de retea) |
| **Batch Many (5000)** | O singura tranzactie gigant | Maxima | Minim (un singur COMMIT final) |

### 4.2. Concluzii Performanta
Utilizarea `addBatch()` si dezactivarea `setAutoCommit` transforma operatiunea dintr-una dependenta de latenta retelei si a discului intr-o operatiune optimizata de memorie. Timpul de executie scade de obicei de la zeci de secunde la cateva sute de milisecunde.

---

## 5. Concluzii Generale
1.  **Izolarea Datelor:** Nivelul implicit al MySQL (`REPEATABLE_READ`) ofera o protectie excelenta impotriva majoritatii anomaliilor, dar vine cu un cost de memorie pentru pastrarea versiunilor de date.
2.  **Siguranta in Concurenta:** Programatorul trebuie sa asigure ordinea accesului la resurse pentru a evita Deadlock-urile in aplicatii multithreaded.
3.  **Optimizare:** Procesarea in loturi (Batching) este obligatorie pentru orice operatiune de scriere voluminoasa pentru a asigura scalabilitatea sistemului.