substituie([], _, _, []):-!.

substituie([E1|T], E1, E2, [E2|Rez]):-
	!, substituie(T, E1, E2, Rez).

substituie([H|T], E1, E2, [H|Rez]):-
	substituie(T, E1, E2, Rez).

main_sublista(L, M, N, Rez):- N1 is N - M, sublista(L, M, N1, Rez).

sublista(_, 1, 1, []):-!.

sublista([_|T], M, N, Rez):-
	M > 1, M1 is M - 1, !, sublista(T, M1, N, Rez).

sublista([H|T], 1, N, [H|Rez]):-
	N1 is N - 1, sublista(T, 1, N1, Rez).
