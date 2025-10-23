
%Definiti un predicat care intoarce cel mai mare divizor comun al numerelor dintr-o clasa.
%cmmdc_lista(lista, res)
%cmmdc(nr1, nr2, res, lista)

cmmdc_lista([H|T], Res) :- cmmdc(H, 0, Res, T).

cmmdc(A, 0, A, []):-!.
cmmdc(A, 0, Res, [H|T]):- cmmdc(A, H, Res, T).
cmmdc(A, B, Res, T):- B =\= 0,
					  A1 is B,
					  B1 is A mod B,
					  cmmdc(A1, B1, Res, T).
