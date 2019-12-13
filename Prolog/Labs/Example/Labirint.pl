wall(4,1).
wall(4,3).
wall(4,4).
not_wall(4,2).
not_wall(3,2).
not_wall(2,2).
not_wall(3,1).
output(3,1).
path(a(I,J), [a(I,J)], History) :- output(I,J).
path(a(I,J), [a(I,J) | P], History) :-
	K is I-1,
	can_go(a(K,J), History),
	path(a(K,J), P, [a(K,J) | History]).

path(a(I,J), [a(I,J) | P], History) :-
	K is I+1,
	can_go(a(K,J), History),
	path(a(K,J), P, [a(K,J) | History]).

path(a(I,J), [a(I,J) | P], History) :-
	L is J-1,
	can_go(a(I,L), History),
	path(a(I,L), P, [a(I,L) | History]).

path(a(I,J), [a(I,J) | P], History) :-
	L is J+1,
	can_go(a(I,L), History),
	path(a(I,L), P, [a(I,L) | History]).

can_go(a(I,J), History) :-
	not_wall(I,J),
	not(member(a(I,J), History)). 

member(H,[H|T]).

member(X,[H|T]) :- 
	member(X,T). 