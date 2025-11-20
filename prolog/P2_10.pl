submultime([], []):-!.

submultime([H|T], [H|R]):-
	submultime(T, R).

submultime([_|T], R):-
	submultime(T, R).

solutie(L, Rez):- findall(R, submultime(L, R), Rez).

main_adauga(L, E, R):- adauga(L, E, 1, 2, R).

adauga([], _, _, _, []):-!.

adauga(L, E, I, I, [E|R]):-
	I1 is I * 2, !,
	adauga(L, E, I, I1, R).

adauga([H|T], E, C, I, [H|R]):-
	C1 is C + 1,
	adauga(T, E, C1, I, R).
