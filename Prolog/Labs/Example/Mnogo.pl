sum_mn([], Q, Q).
sum_mn(P, [], P).

sum_mn([x(Pc,Pp)|Pt], [x(Qc,Qp)|Qt], [x(Pc,Pp)|Rt]) :- 
	Pp<Qp,
	sum_mn(Pt, [x(Qc,Qp)|Qt], Rt).

sum_mn([x(Pc,Pp)|Pt], [x(Qc,Qp)|Qt], [x(Qc,Qp)|Rt]) :- 
	Pp>Qp,
	sum_mn([x(Pc,Pp)|Pt], Qt, Rt).

sum_mn([x(Pc,Pp)|Pt], [x(Qc,Qp)|Qt], [x(Rc,Pp)|Rt]) :- 
	Rc is Pc+Qc,
	Rc=\=0,
	sum_mn(Pt, Qt, Rt).

sum_mn([x(Pc,Pp)|Pt], [x(Qc,Qp)|Qt], Rt) :- 
	Rc is Pc + Qc,
	Rc==0,
	sum_mn(Pt, Qt, Rt).
