
main(L, N, R):- N >= 0, findall(S, subm(L, N, S), R).

subm(_, 0, []).

subm([_|T], N, R):-
	N > 0,
	subm(T, N, R).

subm([H|T], N, [H|R]):-
	N > 0, N1 is N - 1,
	subm(T, N1, R).
