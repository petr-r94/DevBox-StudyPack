fact(1, 1) :-!.

fact(N, V) :-
	M is N-1,
	fact(M, U),
	V is U*N.

fact2(N,F,N,F):-!.

fact2(N,F,N1,F1) :- 
	N2 is N1 + 1,
	F2 is F1 * N2,
	fact2(N,F,N2,F2).

fib(2, 1) :-!.
fib(1, 1) :-!.

fib(N, V) :-
	N1 is N-1,
	fib(N1, U1),
	N2 is N-2,
	fib(N2, U2),
	V is U1+U2.

fib1(1, 1, 1) :-!.

fib1(N, FN, FN1) :-
	N1 is N-1,
	fib1(N1, FN_1, FN),
	FN1 is FN+FN_1.