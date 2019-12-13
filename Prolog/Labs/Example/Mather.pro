% Copyright

implement main
    open core, console

clauses
    parent("Ivan", "Mari").
    parent("Anna", "Mari").
    parent("Mari", "Pavel").
    parent("Mari", "Petr").
    parent("Mari", "Eliz").

    spouse("Ivan", "Anna").
    spouse("Pavel", "Juli").

    male("Ivan").
    male("Pavel").
    male("Petr").

    female("Mari").
    female("Anna").
    female("Eliz").
    female("Juli").

class facts - relatives
    parent: (string Родитель, string Ребенок).
    spouse: (string Муж, string Жена).
    male: (string).
    female: (string).

class predicates
    father: (string Отец, string Ребенок) nondeterm anyflow.
    mother: (string Мать, string Ребенок) nondeterm (o,o).
clauses
    father(X, Y):-
        parent(X, Y),
        male(X).

    mother(X, Y):-
        parent(X, Y),
        female(X).

    run():-
        init(),
 %       file::consult("family.txt", relatives),
        father(X, Y),
            write("Father - ", X, ", Child - ", Y), nl,
        fail;
        mother(X, Y),
            write("Ma - ", X, ", ребенок - ", Y), nl,
        fail;
        if father("Иван", "Петр") then
            write("\nИван является отцом Петра")
        else
            write("\nИван не является отцом Петра")
        end if,
        _ = readLine().

end implement main

goal
    console::runUtf8(main::run).