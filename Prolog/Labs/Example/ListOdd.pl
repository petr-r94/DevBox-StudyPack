sumO(L,S) :- sumOdd(L, 0, S).

sumOdd([], S, S).
sumOdd([H|T], S1, S) :-	R is H mod 2, R>0, S2 is S1 + H, sumOdd(T, S2, S).
sumOdd([_|T], S1, S) :-	sumOdd(T, S1, S).

first([H|T], H).

last([X], X).
last([H|T], X) :- last(T, X).

subList([H|T], N1, N, SL, X) :- R is N1 + 1, R=<N, subList(T, R, N, [H|SL], X).
subList(L, N, N, X, X).

subL(L, N, SL) :- subList(L, 0, N, [], X), reverse(X, SL).