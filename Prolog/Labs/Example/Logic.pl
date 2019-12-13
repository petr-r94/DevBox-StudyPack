name(alex).
name(peter).
name(nik).

place(first).
place(second).
place(therd).

relation(X, Y) :-
	name(X),
	X=peter,
	place(Y),
	not(Y=second),
	not(Y=therd).

relation(X, Y) :-
	name(X),
	X=nik,
	place(Y),
	not(Y=therd).

relation(X, Y) :-
	name(X),
	X=alex,
	place(Y).

solv(X1, Y1, X2, Y2, X3, Y3) :-
	X1=peter, relation(X1, Y1), 
	X2=nik, relation(X2, Y2),
	X3=alex, relation(X3, Y3),
	Y1\=Y2, Y1\=Y3, Y2\=Y3. 
