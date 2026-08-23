diferenta([],[],[]).
diferenta([], _, []):-!.

diferenta([H1|T1], [H2|T2], [H1|Rez]):-
	H1 < H2, !,
	diferenta(T1, [H2|T2], Rez).

diferenta([H1|T1], [H2|T2], [H1|Rez]):-
	H1 > H2, !,
	diferenta([H1|T1], T2, Rez).

diferenta([_|T1], [_|T2], Rez):-
	diferenta(T1, T2, Rez).


adauga([], []):-!.
adauga([H|T], [H,1|Rez]):-
	H mod 2 =:= 0, !,
	adauga(T, Rez).

adauga([H|T], [H|Rez]):-
	adauga(T, Rez).
