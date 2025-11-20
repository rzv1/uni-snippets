
main_vale([H1,H2|T]):- H1 > H2, !, vale(T, H2, 0).

vale([], _, 1):-!.

vale([H|T], E, _):-
	H > E, !, 
	vale(T, H, 1).

vale([H|T], E, 0):-
	H < E,
	vale(T, H, 0).

main_alternant(L, R):- alternant(L, R, 1).

alternant([], 0, _):-!.

alternant([H|T], R1, I):-
	I1 is I * -1,
	alternant(T, R, I1),
	R1 is R + I * H.
