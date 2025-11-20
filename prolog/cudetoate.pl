apartine([H|_], H):-!.
apartine([_|T], E):-
	apartine(T, E).

%invers(Lista mea, [], Inversul listei)
invers([], L, L):-!.
invers([H|T], L, R):-
	invers(T, [H|L], R).

%insertOrd(Lista, E, Rez)
insertOrd([], E, [E]):-!.
insertOrd([H|T], E, [E, H|T]):-
	E =< H, !.
insertOrd([H|T], E, [H|R]):-
	insertOrd(T, E, R).

insertion([X], [X]):-!.
insertion([H|T], R1):-
	insertion(T, R),
	insertOrd(R, H, R1).

divizori(N, N, [N]):-!.
divizori(N, D, [D|R]):-
	N mod D =:= 0, !, D1 is D + 1,
	divizori(N, D1, R).
divizori(N, D, R):-
	D1 is D + 1,
	divizori(N, D1, R).


concat([], L, L):-!.
concat([H|T], L, [H|R]):-
	concat(T, L, R).
	
mainSub(L, R):- findall(Rez, sub1(L, Rez), R).

sub1([], []):-!.
sub1([_|T], R):-
	sub1(T, R).
sub1([H|T], [H|R]):-
	sub1(T, R).


inter([], L, L):-!.
inter(L, [], L):-!.
inter([H1|T1], [H2|T2], [H2|R]):-
	H1 >= H2, !,
	inter(T1, T2, R).
inter([H1|T1], T2, [H1|R]):-
	inter(T1, T2, R).


cmmdc(A, 0, A):-!.
cmmdc(A, B, R):-
	B1 is A mod B,
	cmmdc(B, B1, R).
