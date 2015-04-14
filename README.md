<h3><b>Artificial intelligence repository</b>
	<br>Content</br>
	<hr>
		<br>
		<li><a href="https://github.com/flovera1/AI/tree/master/Bibliography">Biobliography Folder</a>
		</li>
		<p>
			First things first, the bibliography contains two books which I consider are the real basis
			of what the code is about. 
		</p>
	</hr>
	<hr>
		<li><a href="https://github.com/flovera1/AI/tree/master/Decision%20trees">Decision trees</a>
		</li>
			<p>
			This part of the repository is not completely ready, but there is some code that is part of the
			utilities that we'll be using later!
			</p>
	</hr>
	<hr>
	<li><a href="https://github.com/flovera1/AI/tree/master/Genetic%20algorithm%20classical%20problem">
	Genetic algorithms-classical example</a>
	</li>
	<br>
	<p>
		This part of the repository tries to explain what a genetic algorithm is and how "evolution" occurs.
		Unfortunately is also not ready yet. I'm still working in a proper representation of a Chromosome.
		The general idea is to write a genetic algorithm which input is a number and the outout is 
		a formula that generate that number just using: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' and
		operators such as: '+', '-', '*', '/'.
		<br>
		The code is written in java, so, so far to execute it, we must use a javac command:
		<br>
			- javac Chromosome.java
		<br>
		And then:
		<br>
			- java Chromosome
		<br>
	</p>
	</hr>
	<hr>
	<br>
	<li><a href="https://github.com/flovera1/AI/tree/master/K-means%20clustering">Clustering</a>
	</li>
	<br>
	<p>
		Clustering is one of my favorites subjects in artificial intelligence. In this folder you will find an implementation of the K-Means clustering (where K represents the number of the clusters). The data for this case are points(which were generated with "random" numbers), and I did some graphical implementation, so, every cluster was visible (in a plot with a specific color). The code is really straight and simple.
		To execute it, you need to have Java installed.
		<br>
		In order to compile the code:
			- javac KMeans.java
		<br>
		and to execute:
			- java KMeans
		<br>
		The output of the code allows you to do two things: 
			- You will have the numbers classified in the cluster in your bash
			- You will have a representation of the points (this open to the use that you give to your clusters, but in my opinion every data should be represented in a simple and graphical way, because if not, what's the point, isn't it?).
	</p>
	<br>	
	</hr>
	<hr>
		<br>
		<li>
			<a href="https://github.com/flovera1/AI/tree/master/Neural%20networks%20with%20feedforwarding%20(FFNNS)">NNFF (Neural Network with Feed Forward)</a>
		</li>
		<p>
			<b>Abstraction of the problem:</b><br>
			Given a point (x_coordinate, y_coordinate) in the cartesian plane, inside the rectangle (0,0) and (20, 12), classify if the point is inside the circle with center in (10,8) and radius 3.
		</p>
		<p>
		This code was actually a project in my bachelor. <br>
		The representation of a the regular neural network with one inner(hidden) layer. 
		The idea here is that you generate the numbers with a prolog program(generarNumeros.pl), so the txt files represent the training sets. <br>
		<br>
		The code was written in C++.<br>
		The program called: <br>
			-probarMejor.cpp <br>
		it represents the neural network and in it we are trying to build the net and figure out how many neurons and iterations we will need to learn.
		This is one of my favorite pieces of code.
		The way to compile the code is as follow:<br>
			- g++ probarMejor.cpp -o probarMejor <br>
		And then to execute the code:
			- ./probarMejor<br>
		The output of the program is by standard output and again, one part of the information is related to the number of iterations, neurons and the percentage of well classified. 
		<br>
		Another program that we can be delighted of is the "anticonceptivo.cpp" <br>
		How to compile?:<br>
			- g++ anticonceptivo.cpp -o anticonceptivo
			<br>
		executing as follow:<br>
			- ./anticonceptivo <num - neuronas> <proporcion> <entrada> <salida>
			<br>
			or
			<br>
			- ./anticonceptivo 16 0.669 1000.txt file.out
		<br>
		</p>
	</hr>
	<hr>
			<a href="https://github.com/flovera1/AI/tree/master/a%20star">A Star algorithm</a>
			<br>
			<p>
				Some heuristics and useful programs that can be used in any search problem
			</p>
			<br>
			<p>
				This is java code, so, the way to compile is using javac command, for example:
				<br>
					-javac AStarHeuristic.java
				<br>
				And the way to execute in this case would be:
				<br>
					-java AStarHeuristic
			</p>
	</hr>
	<hr>
	<a href="https://github.com/flovera1/AI/tree/master/dfsbfssearch">Graph implementation with classical search algorithms such as DFS, BFS, Branch and Bound </a>
	<br>
	<p>
	Basically what I was looking for here was to be sure that I covered some of the real basics of artificial intelligence and graph theories.<br>
	The way to run this code is running the program called: GraphImplementation.java
	<br>
	To compile:<br>
		- javac GraphImplementation.java
	To execute:<br>
		- java GraphImplementation
		<br>
		And that's it.
	</p>
	</hr>
	<hr>