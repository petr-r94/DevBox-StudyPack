fib1(1, 1, 1) :-!.
fib1(N, F2, F3) :-
	N1 is N-1,
	fib1(N1, F1, F2),
	F3 is F1+F2.
