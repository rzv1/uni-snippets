inversul([], L, L):-!.

inversul([H|T], L, R):-
	inversul(T, [H|L], R).

produsul(L, N, Rez):- inversul(L, [], R), prod(R, N, 0, R1), inversul(R1, [], Rez).

prod([], _, 0, []):-!.
prod([], _, Tr, [Tr]):-!.

prod([H|T], N, Tr, [E|R]):-
	Aux is H * N + Tr,
	E is Aux mod 10, Tr1 is Aux // 10, !,
	prod(T, N, Tr1, R).
