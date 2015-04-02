maxX(20).
maxY(12).

centro(15,6).
radio(3).

generarNum(R,X):-repeat,P is random(1000000), Q is random(1000000), P=<Q,X is P/Q*R,!.

generarNum(X,Y,0):-repeat,maxX(F),maxY(C),
		   generarNum(F,X),generarNum(C,Y),
		   centro(CX,CY),radio(R),
		   P is (X-CX)*(X-CX)+(Y-CY)*(Y-CY),
		   R2 is R*R,
		   P =< R2.
generarNum(X,Y,1):-repeat,maxX(F),maxY(C),
		   generarNum(F,X),generarNum(C,Y),
		   centro(CX,CY),radio(R),
		   P is (X-CX)*(X-CX)+(Y-CY)*(Y-CY),
		   R2 is R*R,
		   P >= R2.

generarTrainingSet(N):-generarTrainingSet(0,N),!.

generarTrainingSet(N,N):-!.
generarTrainingSet(Ind,N):-A is random(2), 
			   generarNum(X,Y,A),
			   imprimirNumeros(X,Y,A),
			   IndNuevo is Ind+1,
			   generarTrainingSet(IndNuevo,N).

imprimirNumeros(X,Y,0):-write(X), write(' '), write(Y), write(' '), write('B'),nl.
imprimirNumeros(X,Y,1):-write(X), write(' '), write(Y), write(' '), write('A'),nl.

