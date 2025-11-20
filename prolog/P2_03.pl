apare([H|_], H):-!.
apare([_|T], E):-
	apare(T, E).

insertionSort([], []):-!.

insertionSort([H|T], R):-
	insertionSort(T, R1),
	\+ apare(T, H),
	insertOrd(H, R1, R), !.

insertionSort([_|T], R):-
	insertionSort(T, R).

insertOrd(X, [], [X]):-!.

insertOrd(X, [H|T], [X,H|T]):-
	X =< H, !.

insertOrd(X, [H|T], [H|R]):-
	insertOrd(X, T, R).
