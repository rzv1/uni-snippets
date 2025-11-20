apartine(E, [E|_]):-!.

apartine(E, [_|T]):-
	apartine(E, T).

intersectie([], _, []):-!.

intersectie([H|T], L, [H|Rez]):-
	apartine(H, L), !,
	intersectie(T, L, Rez).

intersectie([_|T], L, Rez):-
	intersectie(T, L, Rez).


lista(N, N, [N]):-!.

lista(M, N, [M|Rez]):-
	M1 is M + 1,
	lista(M1, N, Rez).
