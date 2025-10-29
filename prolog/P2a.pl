%Model de flux (i, i, o)
main_adauga(E, L, Rez):- adauga(E, L, 1, 2, Rez).

adauga(_, [], _, _, []):-!.

adauga(E, L, Cnt1, Cnt1, [E|Rez]):-
	!,
	New_cnt2 is Cnt1 * 2,
	adauga(E, L, Cnt1, New_cnt2, Rez).

adauga(E, [H|T], Cnt1, Cnt2, [H|Rez]):-
	New_cnt1 is Cnt1 + 1,
	adauga(E, T, New_cnt1, Cnt2, Rez).


liste_adauga([], []):-!.

liste_adauga([H1, H2|T], [H1, C|Rez]):-
	\+ is_list(H1), is_list(H2),
	!,
	main_adauga(H1, H2, C),
	liste_adauga(T, Rez).

liste_adauga([H1, H2|T], [H1|Rez]):-
	\+ is_list(H1), \+ is_list(H2),
	!,
	liste_adauga([H2|T], Rez).


liste_adauga([H1|_], [H1]):-!.
