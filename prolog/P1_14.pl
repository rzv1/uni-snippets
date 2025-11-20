egalitate(L1, L2):- include(L1, L2), include(L2, L1).

include([], _):-!.

include([H|T], L):-
	apartine(H, L), include(T, L).


selectare([H|_], 1, H):-!.

selectare([_|T], N, R):-
	N1 is N - 1, selectare(T, N1, R).
