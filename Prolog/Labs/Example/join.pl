join([], Q, Q).
join([HP|TP], Q, [HP|TR]):-
	join(TP, Q, TR).