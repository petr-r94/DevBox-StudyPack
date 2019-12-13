% Copyright

implement main
    open core, console

class predicates
    nDigit : (integer N, integer I, integer K) procedure (i, i, o).
   nDigit1 : (integer N, integer K1, integer K) determ (i, i, o).
%   nDigit1 : (integer N, integer K) determ (i,i).
    nSum : (integer N, integer K, integer S1, integer S) determ (i,i,i,o).

clauses
    nDigit (N, I, K) :-
        N1=N div 10^I,
        if N1 = 0 then
            K=I
        else
            I1=I+1,
            nDigit (N, I1, K)
        end if.

    nDigit1 (N, K, K) :-
        0=N div 10^K,
%        write ("K1=", K),
        !.

    nDigit1 (N, K, R) :-
        K1=K+1,
        nDigit1 (N, K1, R).

clauses
    nSum (0, -1, S, S) :- !.

    nSum (N, K, S1, S) :-
        N1=N div 10^K,
        N2=N-N1*10^K,
        K2=K-1,
        S2=S1+N1,
        nSum (N2, K2, S2, S).

clauses
   run() :-
%        N=102,
        SN=readLine(),
        N= toTerm(SN),
        nDigit1(N, 1, K),
        write ("K1=", K),
        nl,
        K1=K-1,
        nSum (N, K1, 0, S),
        write ("S=", S),

   fail.

    run() :-
%        nDigit(123, 1, K),
%        write("K=", K),
        succeed. % place your own code here

end implement main

goal
    console::runUtf8(main::run).