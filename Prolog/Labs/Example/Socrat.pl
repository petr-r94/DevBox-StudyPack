mortal(X) :- person(X).

person(platon).
person(socrates).
person(zenon).
person(aristotle).

mortal_report:-  
  write('��� �����:'),nl,
  mortal(X),
  write(X),nl,
  fail.
