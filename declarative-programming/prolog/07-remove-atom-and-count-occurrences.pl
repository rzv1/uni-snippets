%elimina_atom(L, A, Rez)

elimina_atom([], _, []):-!.

elimina_atom([H|T], H, Rez):-
	!,
	elimina_atom(T, H, Rez).

elimina_atom([H|T], E, [H|Rez]):-
	elimina_atom(T, E, Rez).


%nrAparitii(L, E, Nr)

nrAparitii([], _, _):-!.

nrAparitii([H|T], H, Nr):-
	!,
	Nr1 is Nr + 1,
	nrAparitii(T, H, Nr1).

nrAparitii([H|T], E, Nr):-
	nrAparitii(T, E, Nr).

%generare_atomi(L, X)

generare_atomi([], []):-!.

generare_atomi([H|T], [Rez|X]):-
	generare_atomi(T, X).