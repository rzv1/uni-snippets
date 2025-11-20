%problema 14
%Submultimile de suma S cu elemente unei liste, ambele date.

candidat([H|T], H).
candidat([H|T], R):- candidat(T, R).

solutii(L, R):- findall(Rez, main(Rez), R).

main(L, S):- recursiv(L, Rez)
