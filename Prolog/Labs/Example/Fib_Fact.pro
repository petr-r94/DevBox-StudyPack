% Copyright

implement main
    open core, console

class predicates
    fact1 : (integer N, integer F, integer N1, integer F1) procedure (i, o, i, i).
    fact2 : (integer N, integer F) procedure (i, o).

    fib1 : (integer N, integer F) procedure (i, o).
    fib2 : (integer N, integer F1, integer F2) procedure anyflow.
    fib3 : (integer N, integer F, integer N1, integer F1, integer F2) procedure anyflow.

clauses
    fact1 (N,F,N,F) :-!.
    fact1 (N,F,N1,F1) :-
        N2=N1+1,
        F2=F1*N2,
        fact1 (N,F,N2,F2).

clauses
    fact2 (1,1) :-!.
    fact2 (N,F) :-
        N1=N-1,
        fact2 (N1,F1),
        F=F1*N.

 clauses
    fib1 (2,1) :-!.
    fib1 (1,1) :-!.
    fib1 (N, Fib) :-
        N1=N-1,
        fib1 (N1, Fib1),
        N2=N-2,
        fib1 (N2, Fib2),
        Fib=Fib1+Fib2.

 clauses
    fib2 (1,1,1) :-!.
    fib2 (N, Fn, Fn1) :-
        N1=N-1,
        fib2 (N1, Fn_1, Fn),
        Fn1=Fn_1+Fn.

clauses
    fib3 (N,  F,  N,  F,  _) :- !.
    fib3 (N,  F,  N1,  F1,  F2) :-
        N2=N1+1,
        F3=F1+F2,
        fib3 (N,  F,  N2,  F2,  F3).

clauses
    run() :-
        N=8,
%       fact1(N,F,1,1),
        fact2 (N,F),
        write("N=", N, "   Fakt= ", F), nl,

%        fib1 (N, Fib),
%       fib2 (N, Fib, _Fib),
        fib3 (N,  Fib,  1,  1,  1),
        write("N=", N, "   Fib= ", Fib),

        succeed. % place your own code here

end implement main

goal
    console::runUtf8(main::run).