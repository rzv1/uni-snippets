main_elimina(L, E, Rez):- elimina(L, E, 3, Rez).

elimina([], _, _, []):-!.

elimina([H|T], H, N, Rez):-
	N > 0, !,
	N1 is N - 1,
	elimina(T, H, N1, Rez).

elimina([H|T], E, N, [H|Rez]):-
	elimina(T, E, N, Rez).
