divizori(1, _, [1]):-!.

divizori(N, D, [E|R]):-
	D = E, N mod D =:= 0, !, N1 is N // D,
	divizori(N1, D, [E|R]).

divizori(N, D, [D|R]):-
	N mod D =:= 0, !, N1 is N // D,
	divizori(N1, D, R).

divizori(N, D, R):-
	D1 is D + 1, divizori(N, D1, R).
