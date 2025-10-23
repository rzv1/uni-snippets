% Sa se intercaleze un element pe pozitia a n-a a unei liste.

intercalare(E, 1, L, [E|L]).
intercalare(E, N, [H|T], [H|Rez]):-
N1 is N - 1,
intercalare(E, N1, T, Rez).
