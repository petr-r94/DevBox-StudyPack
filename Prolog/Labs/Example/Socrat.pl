mortal(X) :- person(X).

person(platon).
person(socrates).
person(zenon).
person(aristotle).

mortal_report:-  
  write('Они умрут:'),nl,
  mortal(X),
  write(X),nl,
  fail.
