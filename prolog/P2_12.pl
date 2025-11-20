
inloc_apar([], _, _, []):-!.

inloc_apar([H|T], H, E, [E|R]):-
	inloc_apar(T, H, E, R), !.

inloc_apar([H|T], E1, E2, [H|R]):-
	inloc_apar(T, E1, E2, R).
