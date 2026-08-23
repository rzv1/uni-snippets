%main_inloc(L, E, L1, X): inloc(L, E, L1, X).


adauga([], L, L):-!.

adauga([H|T], L, [H|R]):-
	adauga(T, L, R).

inloc([], _, _, []):-!.

inloc([H|T], H, L, [Rez1|Rez]):-
	inloc(T, H, L, Rez),
	adauga(Rez, L, Rez1),
	!.

inloc([H|T], E, L, [H|Rez]):-
	inloc(T, E, L, Rez).

