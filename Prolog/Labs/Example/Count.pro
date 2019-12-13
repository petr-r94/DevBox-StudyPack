% Copyright

implement main
    open core, console

class predicates
    mycount : (integer N, integer I) procedure (i,i).
    count1 : (integer I, integer J) procedure (i,o).
    count2 : (integer N, integer I, integer X) multi (i,i,o).
    test2 : () failure.
    repeat : () multi.
    number1: (positive) -> positive multi.

clauses
    repeat ().
    repeat () :- repeat ().

clauses
    mycount(N,N) :- !.
    mycount(N,I) :-
        K1=I div 100,
        K2=(I-K1*100) div 10,
        K3=I mod 10,
        if K1*K2*K3 = 2*(K1+K2+K3) then
            write("K1= ", K1, " K2= ", K2, " K3= ", K3),
            nl
        end if,
        I1=I+1,
        mycount(N,I1).

clauses
    count1(I, J) :- J=I+1.

    test2 () :-
        I=0,
        repeat,
            count1(I,J),
            write("I= ", J),
            I=1.

clauses
    count2(N, X, X).
    count2(N, I, X) :-
        I<N,
        count2(N, I+1, X).

clauses
    number1(N) = N.
    number1(N) = number1(N - 1):-
        N > 1.

clauses
/*
    run() :-
        mycount(999,111),
        succeed. % place your own code here
*/
   run() :-
%        count2(5,1,X),
%        write(X), nl,
        write(number1(7)), nl,
        fail;
        _=readLine().


end implement main

goal
    console::runUtf8(main::run).