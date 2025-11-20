
jmekerie([]):-!.

jmekerie([_,_|T]):-
	jmekerie(T).


minim([E], E):-!.

minim([H|T], H):-
	minim(T, M), H < M, !.

minim([_|T], M):-
	minim(T, M).

main_elimina(L, R):- minim(L, M), elimina(L, 1, M, R).

elimina(L, 0, _, L):-!.

elimina([H|T], 1, H, R):-
	elimina(T, 0, H, R), !.

elimina([H|T], 1, E, [H|R]):-
	elimina(T, 1, E, R).
