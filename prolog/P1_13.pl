apare([H|_], H):-!.

apare([_|T], E):-
	apare(T, E).


trans([], []):-!.

trans([H|T], [H|Rez]):-
	\+ apare(T, H), !, trans(T, Rez).

trans([_|T], Rez):-
	trans(T, Rez).



