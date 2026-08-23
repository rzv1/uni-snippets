%adauga(L, E, Lsub, Rez)

adauga([], _, _, []):-!.

adauga([H|T], H, L, [L|Rez]):-
	!,
	adauga(T, H, L, Rez).

adauga([H|T], E, L, [H|Rez]):-
	adauga(T, E, L, Rez).

%elimina(L, N)
main_elimina(L, N, Rez):- elimina(L, N, 1, Rez).

elimina([], _, _, []):-!.

elimina([_|T], N, N, Rez):-
	N1 is N + 1, !,
	elimina(T, N, N1, Rez).

elimina([H|T], N, I, [H|Rez]):-
	I1 is I + 1, !,
	elimina(T, N, I1, Rez).