intercalare(L, _, 0, L):-!.

intercalare([H|T], E, N, [E,H|Rez]):-
	N = 1, !, N1 is N - 1,
	intercalare(T, E, N1, Rez).

intercalare([H|T], E, N, [H|Rez]):-
	N1 is N - 1,
	intercalare(T, E, N1, Rez).



