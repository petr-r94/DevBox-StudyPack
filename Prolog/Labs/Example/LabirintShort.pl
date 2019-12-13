    not_wall(1,3).
    not_wall(2,2).
    not_wall(2,3).
    not_wall(2,4).
    not_wall(3,2).
    not_wall(3,4).
    not_wall(4,1).
    not_wall(4,2).    
    not_wall(4,4).
    not_wall(4,5).    
    not_wall(5,2).
    not_wall(5,3).
    not_wall(5,4).    
    not_wall(6,3).

    output(1,3).
    output(4,1).
    output(4,5).

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

shortest_path(A, _) :-
	asserta(short_path([], 999999)),
	path(A, P_New, [A]),
	length(P_New, L_New),
        short_path(_, L_Old),
        compare1(P_New, L_New, L_Old).

shortest_path(_, P) :- 
	retract(short_path(P, _)).

compare1(P_New, L_New, L_Old) :-
        L_New < L_Old,
        retract(short_path(_, _)),
        asserta(short_path(P_New, L_New)),
        fail.
