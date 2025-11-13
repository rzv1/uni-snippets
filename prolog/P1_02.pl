




main_adaugare(L, V, Rez):-adaugare(L, 1, 1, V, Rez).
adaugare([], _, _, _, []):-!.

adaugare([H|T], Poz, Poz, V, [H,V|Rez]):-
	Poz1 is Poz*2,
	I is Poz+1,
	!,
	adaugare(T, Poz1, I, V, Rez).

adaugare([H|T], Poz, I, V, [H|Rez]):-
	I1 is I+1,
	adaugare(T, Poz, I1, V, Rez).
