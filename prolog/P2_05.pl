maxim([H], H):-!.

maxim([H|T], H):-
	maxim(T, M), H > M, !.

maxim([_|T], M):-
	maxim(T, M).

main_gaseste(L, R):- maxim(L, M), gaseste(L, M, 1, R).

gaseste([], _, _, []):-!.

gaseste([H|T], H, I, [I|R]):-
	I1 is I + 1,
	gaseste(T, H, I1, R).

gaseste([H|T], E, I, R):-
	I1 is I + 1,
	gaseste(T, E, I1, R).
