%Model de flux (i, o)
main_poz_max(L, Rez):- 
	max_list(L, Max),
	poz_max(L, 1, Max, Rez).

poz_max([], _, _, []):-!.

poz_max([H|T], Cnt, Max, [Cnt|Rez]):-
	H =:= Max, !,
	Cnt1 is Cnt+1,
	poz_max(T, Cnt1, Max, Rez).

poz_max([_|T], Cnt, Max, Rez):-
	Cnt1 is Cnt+1,
	poz_max(T, Cnt1, Max, Rez).

%Model de flux(i, o)
poz_liste([], []):-!.
	
poz_liste([H|T], [C|Rez]):-
	is_list(H), !,
	main_poz_max(H, C),
	poz_liste(T, Rez).

poz_liste([H|T], [H|Rez]):-
	number(H), !,
	poz_liste(T, Rez).





maxim([E], E):-!.
maxim([H|T], H):-
	maxim(T, Max),
	H >= Max, !.
maxim([_|T], Max):-
	maxim(T, Max).
