/** ЛАБОРАТОРНЫЕ РАБОТЫ. ВАРИАНТ №1
 * =========================================================
 * Задание № 1. Простые предикаты

1 Предикат isParallel, возвращающая True, если два отрезка, концы которых задаются в аргументах функции, параллельны (или лежат на одной прямой).

Например, значение выражения isParallel (1,1) (2,2) (2,0) (4,2) должно быть равно True, поскольку отрезки (1, 1) − (2, 2) и (2, 0) − (4, 2) параллельны.
 *=========================================================
 */
isParallel(X1,Y1, X2,Y2, X3,Y3, X4,Y4):-
	(((X1 - X2) * (Y3-Y4))  =:= ((Y1-Y2) * (X3-X4)) ) -> writeln("Параллельны!"), true; writeln("Не параллельны!"), fail.

/**=========================================================
 * Задание № 2. Сложные функции

1. Дано целое число. Найти количество и сумму его цифр. Результат вернуть в виде пары
значений.
 *
 *=========================================================
 */
printPair(Nu, Su, Cd):- write("У числа: "), writeln(Nu), write("Сумма цифр: "), writeln(Su), write("Количество цифр: "), writeln(Cd), true.

digits_count(Number, 1):-
	Number >= 0, Number =< 9, !.

digits_count(Number, Kol):-
  NumberWithoutDigit is Number//10,
  digits_count(NumberWithoutDigit, CountWithoutDigit),
  Kol is CountWithoutDigit + 1.

sum(Number, Number):- Number < 10, ! .
sum(Number, Summa):-
	M is Number mod 10,
	B is Number//10,
	sum(B,N1),
	Summa is N1+M.

cAs(Number):-
	sum(Number, Summa),
	digits_count(Number, Kol),
	printPair(Number, Summa, Kol).
/**=========================================================
 * Задание № 3. Работа со списками

1. Дан список целых чисел. Сформировать новый список, содержащий только нечетные элементы исходного.
 *
 *=========================================================
 */

getEl(1, [Elem|_Tail], Elem):-!.
getEl(Index, _List, _Elem):-
  Index < 1, !, fail.
getEl(Index, [_Head|Tail], Elem):-
  NextIndex is Index - 1,
  getEl(NextIndex, Tail, Elem).

lengthSpisok(List, Length):-
  lengthSpisok(List, 0, Length).

lengthSpisok([ ], Length, Length):-!.
lengthSpisok([_Head|Tail], Buffer, Length):-
  NewBuffer is Buffer + 1,
  lengthSpisok(Tail, NewBuffer, Length).

isOdd(Elem):- (Elem mod 2 =:= 1) -> true; false.

newSpisok(L1, L2):-
	getEl(1, L1, Odd),
	append(L2, [Odd], L3),
	write("Формируемый список: "), writeln(L3),
	L1 = [ _ |  Tail1],
	Tail1 = [ _ | Tail2],
	newSpisok(Tail2, L3).

oddSpisok(L1, L2, K):-
	getEl(K, L1, Odd),
	isOdd(Odd) -> write("Добавлен "),
	append(L2, [Odd], L3),
	write("нечетный элемент: ["), write(Odd), writeln("]"),
	oddSpisok(L1, L3, K+1); oddSpisok(L1, L3, K+1).
