sum([], 0).
sum([H|T], S) :- 
	sum(T, S_T),
	S is S_T + H.

sum_list([], S, S).

sum_list([H|T], N, S) :- 
	N_T is H + N,
	sum_list(T, N_T, S).

min(X,Y,X) :- 
	X<Y, !.
min(_,Y,Y).

min_list([X], X).

min_list([H|T], M) :- 
	min_list(T, M_T),
	min(H, M_T, M).

permutation([X,Y|T], [Y,X|T]) :- 
	X>Y,!.

permutation([X|T], [X|T1]) :- 
	permutation(T, T1).

buble(L,L1) :- 
	permutation(L, LL),
	!,
	buble(LL,L1).

buble(L,L).
