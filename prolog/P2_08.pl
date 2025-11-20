inv([], L, L):-!.
inv([H|T], L, R):-
	inv(T, [H|L], R).

succesor(L, R):- inv(L, [], R1), succ(R1, 1, R2), inv(R2, [], R).

succ([], 0, []):-!.
succ([], Tr, [Tr]):-!.

succ([H|T], Tr, [E|R]):-
	E is (H + Tr) mod 10, Tr1 is (H + Tr) // 10, !,
	succ(T, Tr1, R).
