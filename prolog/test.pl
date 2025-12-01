
main(L, S, R):- S > 0, findall(Sub, submultimeSuma(L, S, Sub), R).

submultimeSuma(_, 0, []):-!.

submultimeSuma([_|T], S, R):-
	S > 0,
	submultimeSuma(T, S, R).

submultimeSuma([H|T], S, [H|R]):-
	S > 0, S1 is S - H,
	submultimeSuma(T, S1, R).