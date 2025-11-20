
inversare([], L, L):-!.

inversare([H|T], L, R):-
	inversare(T, [H|L], R).

suma_main(L1, L2, Rez):- inversare(L1, [], R1), inversare(L2, [], R2), 
					suma(R1, R2, 0, R), inversare(R, [], Rez).

suma([], [], 1, [1]):-!.

suma([], [], _, []):-!.

suma([], [H|T], Tr, [E1|R]):-
	E1 is (H + Tr) mod 10, Tr1 is (H + Tr) // 10, !,
	suma([], T, Tr1, R).

suma([H|T], [], Tr, [E1|R]):-
	E1 is (H + Tr) mod 10, Tr1 is (H + Tr) // 10, !,
	suma(T, [], Tr1, R).

suma([H|T], [H1|T1], Tr, [E1|R]):-
	E1 is (H + H1 + Tr) mod 10, Tr1 is (H + H1 + Tr) // 10, !,
	suma(T, T1, Tr1, R).
