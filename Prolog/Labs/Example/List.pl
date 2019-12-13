length1([], 0).

length1([_|T], L) :-
	length1(T, L_T),
	L is L_T + 1.

delete_all(_, [], []).

delete_all(X, [X|L], L1) :-
	delete_all(X, L, L1).

delete_all(X, [Y|L], [Y|L1]) :-
	X=\=Y,
	delete_all(X, L, L1).


member(H,[H|T]).

member(H,[Y|T]) :- 
	member(H,T).

conc([], X, X).

conc([H|T1], X, [H|T2]) :- 
	conc(T1, X, T2).

last(L, X) :- 
	conc(_, [X], L).

delete(A,[A|X],X).
delete(A,[B|X],[B|Y]):-
            delete(A,X,Y).

permutation([],[]).
permutation([A|X],Y):-
         delete(A,Y,Y1),
         permutation(X,Y1).

append([],L,L).
append([X|L1],L2,[X|L3]) :-
	append(L1,L2,L3).

revers([], []).
revers([H|T], L) :-
	revers(T,Z), append(Z, [H], L).

revers1(L1, L2) :- rev(L1, [], L2).
rev([], L, L).
rev([X|L], L2, L3) :- rev(L, [X|L2], L3).





