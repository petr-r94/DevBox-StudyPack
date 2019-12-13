% Copyright

implement main
    open core, console

class facts
numb1 : (integer N).

class predicates
test1 : () nondeterm.

clauses
    numb1(1).
    numb1(2).
    numb1(3).
    numb1(4).
    numb1(5).
    numb1(6).
    numb1(7).
    numb1(8).
    numb1(9).
    numb1(0).

 test1() :-
    numb1(X),
    numb1(Y),
    numb1(Z),
    X*Y*Z=2*(X+Y+Z),
    write(X,Y,Z),
    nl.

clauses
    run() :-
        test1(),
        fail.
    run() :-
        succeed. % place your own code here

end implement main

goal
    console::runUtf8(main::run).