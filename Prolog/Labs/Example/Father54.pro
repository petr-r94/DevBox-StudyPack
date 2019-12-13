% Copyright

implement main
    open core, console

class predicates
    father_sun : (integer F) determ (i).
    father_rec : (integer X) determ (i).
clauses
    father_rec(F) :-
        F<54, !,
        not (father_sun(F)),
        F1=F+1,
        father_rec(F1).

    father_sun(F) :-
        S=54-F,
        F+3=3*(S+3),
        write("F= ", F, "           S= ", S).

    run() :-
        console::init(),
        father_rec(1),
        fail.

 %       write("F=", F, "S=", S),
        run() :-
            succeed. % place your own code here

end implement main

goal
    console::runUtf8(main::run).