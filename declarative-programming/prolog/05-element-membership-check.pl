aparitie([], _):-false.

aparitie([H|_], V):-
	H = V, !.

aparitie([_|T], V):-
	aparitie(T, V).
