
apare([H|_], H):-!.

apare([_|T], E):-
	apare(T, E).

eMultime([]).

eMultime([H|T]):-
	\+ apare(T, H), eMultime(T).

%reuniune(L1, L2, Rez)

reuniune([], L, L):-!.

reuniune([H|T], L, Rez):-
	apare(L, H), !,
	reuniune(T, L, Rez).

reuniune([H|T], L, [H|Rez]):-
	reuniune(T, L, Rez).

pereche([], _, []):-!.

pereche([H|T], E, Rez1):-
	pereche(T, E, Rez),
	Rez1 is [E,H]+Rez.

%perechi(L, R)

perechi([], []):-!.

perechi([H|T], [R|Rez]):-
	pereche(T, H, R),
	perechi(T, Rez).
