generare([], _, _, []):-!.

generare([H|T], H, L, R1):-
	generare(T, H, L, R), !, aux(L, R, R1).

generare([H|T], E, L, [H|R]):-
	generare(T, E, L, R).


aux([], L, L):-!.

aux([H|T], L, [H|R]):-
	aux(T, L, R).
