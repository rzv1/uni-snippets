
insertion_sort([], []).
insertion_sort([H|T], R):-
	insertion_sort(T, RT),
	insert_ord(H, RT, R).

insert_ord(X, [], [X]):-!.

insert_ord(X, [H|T], [X,H|T]):-
	X =< H, !.

insert_ord(X, [H|T], [H|R]):-
	insert_ord(X, T, R).


