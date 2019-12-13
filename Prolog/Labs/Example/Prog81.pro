% Copyright

implement main
    open core, console
class predicates
    pr81 : (integer A, integer P) procedure (i, i).

clauses
    pr81(A, P) :-
        if P=81 then
            write("yes")
        elseif P>100 then
            write("no")
        else
            P1=P*A,
            pr81(A, P1)
        end if.

clauses
    run() :-
        A=9,
        P=1,
        pr81(A, P),
        succeed. % place your own code here

end implement main

goal
    console::runUtf8(main::run).