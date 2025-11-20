apare([H|_], H):-!.
apare([_|T], E):-
	apare(T, E).

insertOrd(X, [], [X]):-!.

insertOrd(X, [H|T], [X, H|T]):-
	X =< H, !.

insertOrd(X, [H|T], [H|R]):-
	insertOrd(X, T, R).

interclasare([], L, L):-!.

interclasare([H|T], L, R):-
	\+ apare(L, H),
	insertOrd(H, L, L1),
	interclasare(T, L1, R), !.

interclasare([H|T], L, R):-
	interclasare(T, L, R).
