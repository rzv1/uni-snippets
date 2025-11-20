%elimina(L, Rez)

main_elimina(L, Rez):- elimina(L, L, Rez).

elimina([], _, []):-!.

elimina([H|T], L, Rez):-
	numara(L, H, N), N > 1, !,
	elimina(T, L, Rez).

elimina([H|T], L, [H|Rez]):-
	elimina(T, L, Rez).

%numara(L, E, N)

numara([], _, 0).

numara([H|T], H, N1):-
	numara(T, H, N),
	N1 is N + 1, !.

numara([_|T], E, N):-
	numara(T, E, N).

%maxim(L, M)

maxim([T], T).

maxim([H|T], M1):-
	maxim(T, M), H > M, !, M1 = H.

maxim([H|T], M1):-
	maxim(T, M), H =< M, M1 = M.

main_eliminaMax(L, Rez):- 
	maxim(L, M),
	eliminaMax(L, M, Rez).

eliminaMax([], _, []):-!.

eliminaMax([H|T], H, Rez):-
	!, eliminaMax(T, H, Rez).

eliminaMax([H|T], M, [H|Rez]):-
	eliminaMax(T, M, Rez).
