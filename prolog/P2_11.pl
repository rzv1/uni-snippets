ePrim(N, N, 0):-!.


ePrim(N, Div, 0):-
	0 =:= N mod Div, !, N1 is N // Div,
	ePrim(N1, Div, 1).

ePrim(N, Div, 0):-
	N =< Div * Div, !,
	ePrim(N, N, 0).

ePrim(N, Div, 0):-
	Div1 is Div + 1,
	ePrim(N, Div1, 0).

duplicare([], []):-!.

duplicare([H|T], [H,H|R]):-
	ePrim(H, 2, 0), !, 
	duplicare(T, R).

duplicare([H|T], [H|R]):-
	duplicare(T, R).
