main1(L, R):- findall(S, sub1(L, S), R).

coliniar( (X1,Y1), (X2,Y2), (X3,Y3) ):-
	(X2 - X1)*(Y3 - Y1) =:= (Y2 - Y1)*(X3 - X1).

coliniar_lista(_, []):-!.
coliniar_lista(_, [_]):-!.

coliniar_lista(P, [P1, P2|T]):-
	coliniar(P1, P2, P),
	coliniar_lista(P, [P2|T]).

sub1([], []).
sub1([P], [P]).

sub1([_|T], R):-
	sub1(T, R).

sub1([P|T], [P|R]):-
	coliniar_lista(P, R),
	sub1(T, R).
	
