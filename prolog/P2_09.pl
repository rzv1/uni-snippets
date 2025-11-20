
main_sterg(L, X):- sterg(L, X, 0).

sterg([], [], _):-!.

sterg([H|T], R, Last):-
	Last + 1 =:= H, !,
	sterg(T, R, H).

sterg([H|T], [H|R], Last):-
	sterg(T, R, H).
