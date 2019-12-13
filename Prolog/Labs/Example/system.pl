versh(Vid, Vopr, Dugi).

duga(Otv, Vid).

menu:-
	repeat,nl,
	write('Хотите ли вы:'), nl,
	write('1) Загрузить дерево'), nl,
	write('2) Сохранить дерево'), nl,
	write('3) Добавить вершину'), nl,
	write('4) Удалить вершину'), nl,
	write('5) Добавить дугу'), nl,
	write('6) Удалить дугу'), nl,
	write('7) Просмотреть дерево'), nl,
	write('8) Совершить обход дерева'), nl,
	write('9) Стоп'), nl,
	write('Введите 1-9'), nl,
	write(''), nl,
	read(V), nl,
	exec(V).

exec(1):-
	write('Имя файла?'),
	read(F), nl,
	write('Чтение файла...'),
	write(F),
	reconsult(F),
	write('...закончилось'), nl,
	fail.

exec(2):-
	write('Имя файла'),
	read(F),
	open(F, Bl, write),!, nl,
	write('запись в файл...'),
	write(F),
	assertz(versh(-1, -1, -1)),
	versh(Vid, B, Dugi),
	save_versh(Vid, B, Dugi, Bl),
	write('...закончилось'), nl,
	close(Bl),!,
	fail.

exec(3):-
	read_new_id(Vid),
	write('Введите вопрос, в конце напишите слово конец'), nl,
	read_vopr(Vopr),
	read_dugi(Dugi),
	not(cicl(Vid,Dugi)),
	assertz(versh(Vid, Vopr, Dugi)),!,
	fail.
	
exec(4):-
	read_old_id(Vid),
	del_versh(Vid),!,
	fail.

exec(5):-
	write('Из вершины'),
	read_old_id(Vid),
	read_dugu(Duga),
	not(cicl(Vid,[Duga])),
	add_dugu(Vid, Duga), !,
	fail.

exec(6):-
	read_old_id(Vid), 
	read_dugu(Duga),
	del_dugu(Vid, Duga), !,
	fail.

exec(7):-
	read_old_id(Vid), nl,
	write('Просмотр дерева'), nl,
	show_tree(Vid), !,
	fail.

exec(8):-
	read_old_id(Vid), nl,
	obhod_tree(Vid), !,
	fail.

exec(9):-
	nl, write('Bye, bye!!!'), nl, !.


save_versh(-1, -1, -1, _):- !,
	retract(versh(-1, -1, -1)).

save_versh(Vid, B, Dugi, Bl):-
	write(Bl, versh(Vid, B, Dugi)),
	write(Bl, '.'),
	nl(Bl), !,
	fail.

cicl(Vid, Dugi):-
	vedet(Vid, Dugi, P),
	write('Дуги'), write(Dugi), nl,
	write('Вызывают образование цикла:'),
	write(P), nl, !.

read_new_id(Vid):-
	repeat,
	write('Идентификатор новой вершины?'),
	read(Vid), nl,
	no_exist(Vid), !.

read_old_id(Vid):-
	repeat,
	write('Идентификатор вершины?'),
	read(Vid), nl,
	exist(Vid), !.

no_exist(Vid):-
	versh(Vid, _, _),
	write('Такой идентификатор уже есть!'), nl,
	!, fail.

no_exist(_).

exist(Vid):-
	versh(Vid, _, _), !.

exist(_):-
	write('Такого идентификатора нет!'), nl,
	!, fail.

read_dugi(Dugi):-
	repeat, nl,
	write('Сколько всего дуг?'),
	read(N), nl,
	N=0,
	read_n_dugi(N, Dugi).

read_n_dugi(0, []):- !.

read_n_dugi(N, [Duga|Dugi]):-
	M is N-1,
	read_n_dugi(M, Dugi),
	write('Дуга'), write(N), nl, nl,
	read_dugu(Duga), !.

read_dugu(duga(Otv, Vid)):-
	nl, write('Ответ?'),
	read(Otv), nl, 
	write('К вершине'),
	read_old_id(Vid).

read_vopr(Vopr):-
	write('>'),
	current_input(Stream),
	read_line_to_codes(Stream, Str1),
	string_to_atom(Str1, Str),
	write('read_vopr'), write(Str), nl,
	cont_read(Str, Vopr).

cont_read('konec', []):- !.

cont_read(Str, [Str|Vopr]):-
	write('cont_read'),
	write([Str|Vopr]), nl,
	read_vopr(Vopr).

write_vopr([]):- !.

write_vopr([H|T]):-
	nl, write(H),
	write_vopr(T).

show_tree(Vid):-
	show_dugi([duga('??', Vid)], 0, 8).

show_dugi([duga(D, Vid)|Dugi], M, S):-
	MI is M*S,
	tab(MI), write(' '),
 	write(D), nl,
	tab(MI), write('-----------+'),
	write('['),
	write(Vid),
	write(']'), nl,
	sh_tree(Vid, M, S),
	show_dugi(Dugi, M, S).

sh_tree(Vid, N, S):-
	versh(Vid, B, Dugi),
	M is N+1,
	show_dugi(Dugi, M, S).

del_versh(Vid):-
	retract(versh(Vid, B, Dugi)),
	del_all_vh_dugi(Vid),
	nl, write('Вершина уничтожена'), nl.

del_all_vh_dugi(Vid):-
	assertz(versh(-1, -1, -1)),
	retract(versh(Vid2, B, Dugi)),
	del2(Vid2, B, Dugi, Vid), !.

del2(-1, -1, -1, _).

del2(Vid2, B, Dugi, Vid):-
	del_list(Dugi, duga(D, Vid), Dugi2),
	assertz(versh(Vid2, B, Dugi2)), !,
	fail.

del_list([], E, []):- !.

del_list([E|T], E, T2):- !,
	del_list(T, E, T2).

del_list([H|T], E, [H|T2]):- !,
	del_list(T, E, T2).

add_dugu(Vid, D):-
	versh(Vid, B, Dugi),
	member(D, Dugi), !,
	nl, write('уже существует !!!'), nl.

add_dugu(Vid, duga(D, Vid2)):-
	versh(Vid2, _, _),
	retract(versh(Vid, B, Dugi)),
	assertz(versh(Vid, B, [duga(D, Vid2) | Dugi])),
	nl, write('дуга добавлена'), nl.

del_dugu(Vid, D):-
	retract(versh(Vid, B, Dugi)),
	del_list(Dugi, D, Dugi2),
	assertz(versh(Vid, B, Dugi2)),
	nl, write('дуга уничтожена'), nl.

vedet([duga(D, Vid)|T], Vid2, P):-
	vesti(Vid, Vid2, P), !.

vedet([_|T], Vid2, P):-
	vedet(T, Vid2, P).

vesti(Vid, Vid, [Vid, Vid]):-!.

vesti(Vid1, Vid2, [Vid1, Vid2]):-
	versh(Vid1, V, Dugi),
	member(duga(D, Vid2), Dugi), !.

vesti(Vid1, Vid2, [Vid1, P]):-
	versh(Vid1, V, Dugi),
	vedet(Dugi, Vid2, P).

obhod(Cvid):-
	versh(Cvid, V, Dugi),
	obrab_dugi(Dugi, V).

obrab_dugi([], V):- !,
	write_vopr(V).

obrab_dugi(Dugi, V):-
	vvesti_otvet(V, Dugi, Otv),
	member(duga(Otv, V), Dugi),
	obhod(V).

vvesti_otvet(V, Dugi, Otv):-
	repeat,
	write_vopr(V),
	read(Otv),
	member(duga(Otv, _), Dugi), !.
