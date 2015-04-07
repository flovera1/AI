import java.util.Iterator;
import java.util.Random;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.Math;

public class RedNeural {

	int numNodosEntrada;
	int numNodosIntermedios;
	int numNodosSalida;
	
	double [][] weight_input_layer;
	double [][] weight_output_layer;
	double tasaAprendizaje;
	
	public RedNeural(int numNodosEntrada, 
				     int numNodosIntermedios, 
				     int numNodosSalida, 
				     double tasaAprendizaje) {
		
		super();
		
		this.numNodosEntrada = numNodosEntrada;
		this.numNodosIntermedios = numNodosIntermedios;
		this.numNodosSalida = numNodosSalida;
		this.tasaAprendizaje = tasaAprendizaje;
		
		weight_input_layer = new double[numNodosEntrada+1][numNodosIntermedios];
		
		Random generator = new Random();
		
		for (int i =0; i<numNodosEntrada+1;i++){
			for (int j = 0; j < numNodosIntermedios; j++){
				weight_input_layer[i][j] = generator.nextDouble();
			}
		}
		
		weight_output_layer = new double [numNodosIntermedios+1][numNodosSalida];
		for (int i =0; i<numNodosIntermedios+1;i++){
			for (int j = 0; j < numNodosSalida; j++){
				weight_output_layer[i][j] = generator.nextDouble();
			}
		}
	}
	
	void  feed_forward(double [] valor_entrada, double [] valores_intermedios, double [] valor_salida){
		double acum;
		
		//Calculo de los valores intermedios.
		for(int i = 0; i < numNodosIntermedios; i++){
			//Calculo de net
			acum =0;
		
			for (int j = 0 ; j < numNodosEntrada; j++){
				acum+=weight_input_layer[j][i]*valor_entrada[j];
			}
			
			// Aplicacion de la funcion sigmoidal. 
			valores_intermedios[i] = sigmoid(acum+weight_input_layer[numNodosEntrada][i]);
		}
		
			//Calculo de los valores intermedios.
		for(int i = 0; i < numNodosSalida; i++){
			//Calculo de net
			acum =0;
		
			for (int j = 0 ; j < numNodosIntermedios; j++){
				acum+=weight_output_layer[j][i]*valores_intermedios[j];
			}
			
			// Aplicacion de la funcion sigmoidal. 
			valor_salida[i] = sigmoid(acum+weight_output_layer[numNodosIntermedios][i]);
		}
	}
	
	double sigmoid(double y){
		return 1/(1+Math.exp(-y));
	}
	
	double []  calcularSalida(double [] valor_entrada){
		
		double [] valor_salida = new double [numNodosSalida] ;
		
		double [] valores_intermedios = new double [numNodosIntermedios];
		
		feed_forward(valor_entrada, valores_intermedios, valor_salida);
		
		return valor_salida ;
		
	}    
	
	double error_output(double output, double target){
		return output*(1-output)*(target-output);
	}
	
	void resolve_case(double [] valor_entrada, double [] target){
		
		double [] valores_intermedios = new double [numNodosIntermedios];
		double [] valor_salida =  new double [numNodosSalida];
		
		double [] error_intermedios =  new double [numNodosIntermedios];
		double [] error_salida =  new double [numNodosSalida];

		// Feed forward.
		feed_forward(valor_entrada, valores_intermedios,valor_salida);
		
		
		//Calculo del error de la capa de salida.
		for (int i = 0 ; i< numNodosSalida; i++){
			error_salida[i] = error_output(valor_salida[i], target[i]);
		}
		
		
		double acum;
		
		//Calculo de error de cada neurona intermedia
		for(int i = 0; i < numNodosIntermedios; i++){
			acum = 0; 
			for(int j=0; j < numNodosSalida; j++){
				acum += weight_output_layer[i][j]*error_salida[j];
			}
			error_intermedios[i] =  valores_intermedios[i]*(1-valores_intermedios[i])*acum;
		}
		
		
		//Actualizar pesos de la capa intermedia a la de salida
		for(int j=0; j < numNodosSalida; j++){
		
			for(int i = 0 ; i < numNodosIntermedios; i++){
				weight_output_layer[i][j] += tasaAprendizaje*error_salida[j]*valores_intermedios[i];
			}
			//weight_output_layer[numNodosIntermedios][j] += tasaAprendizaje*error_salida[j];
		}
		
		
		
		//Actualizar pesos de la capa de entrada a la capa de salida. 
		for(int i = 0; i<numNodosIntermedios; i++){
			for (int j = 0; j<numNodosEntrada; j++){
				weight_input_layer[j][i] += tasaAprendizaje*
											error_intermedios[i]*
											valor_entrada[j];	
			}
			//weight_input_layer[numNodosEntrada][i]+=tasaAprendizaje*
			//								error_intermedios[i];
		}
		
	}
	
	//entrenamiento
	void resolve_set_cases(double [][] entrada, double [][] target,int size){
		
		for(int i = 0; i<size; i++){		
			resolve_case(entrada[i], target[i]);//el target se inicializa en el main
		}
	}
	
	public void writeToFile (String fileName){
		try{
			  // Create file 
			  FileWriter fstream = new FileWriter(fileName);
			  BufferedWriter out = new BufferedWriter(fstream);
			  
			  out.write(Integer.toString(numNodosEntrada) + " ");
			  out.write(Integer.toString(numNodosIntermedios) + " ");
			  out.write(Integer.toString(numNodosSalida) + " ");
			  out.write(Double.toString(tasaAprendizaje) + "\n");
			  
			  for (int i =0; i<numNodosEntrada+1;i++){
				for (int j = 0; j < numNodosIntermedios; j++){
					  out.write(Double.toString(weight_input_layer[i][j]) + " ");
				}
				out.write ("\n");
			  }

			  for (int i =0; i<numNodosIntermedios+1;i++){
				for (int j = 0; j < numNodosSalida; j++){
					out.write(Double.toString(weight_output_layer[i][j]) + " ");
				}
				out.write ("\n");
			  }
	
			  out.write ("\n");			  
			  
			  //Close the output stream
			  out.close();
			  }
		catch (Exception e){//Catch exception if any
			  System.err.println("Error: " + e.getMessage());
			  }
	}

	public RedNeural (String fileName){
		
		try {
		    BufferedReader in = new BufferedReader(new FileReader(fileName));
		    String str;
		    
		    str = in.readLine();
		    StringTokenizer st = new StringTokenizer(str, " ");
		    
		    this.numNodosEntrada =  Integer.valueOf(st.nextToken()).intValue();
			this.numNodosIntermedios =  Integer.valueOf(st.nextToken()).intValue();
			this.numNodosSalida =  Integer.valueOf(st.nextToken()).intValue();
			this.tasaAprendizaje =  Double.valueOf(st.nextToken()).doubleValue();
 
			weight_input_layer = new double[numNodosEntrada+1][numNodosIntermedios];
			weight_output_layer = new double [numNodosIntermedios+1][numNodosSalida];
			
			for (int i =0; i<numNodosEntrada+1;i++){
				str = in.readLine();
				st = new StringTokenizer(str, " ");
				for (int j = 0; j < numNodosIntermedios; j++){
					weight_input_layer[i][j] = Double.valueOf(st.nextToken()).doubleValue();
				}
			}
				  
			for (int i =0; i<numNodosIntermedios+1;i++){
				str = in.readLine();
				st = new StringTokenizer(str, " ");
				for (int j = 0; j < numNodosSalida; j++){
					weight_output_layer[i][j] =  Double.valueOf(st.nextToken()).doubleValue();
				}

			}
		    
		    in.close();
		} catch (IOException e) {
			System.out.println("Error leyendo!");
		}
					
	}

	public static void getTrainingSet(double [][] valoresEntrada, 
									  double [][] target,
									  int sizeTrainingSet,
									  int numNodosEntrada,
									  int numNodosSalida,
									  String filename){
		
		try {
		    BufferedReader in = new BufferedReader(new FileReader(filename));
		    String str;
		    int numCaso = 0;
		    StringTokenizer st;
		    
		    for (numCaso=0;numCaso<sizeTrainingSet;numCaso++){
		    	
		    	if ((str = in.readLine()) == null){
		    		System.out.println("Error en el archivo. ");
		    	}
				st = new StringTokenizer(str,",");
				
				for (int i = 0; i < numNodosEntrada; i++){
					valoresEntrada[numCaso][i] = Double.valueOf(st.nextToken()).doubleValue();
				}
				
				for (int i = 0; i < numNodosSalida; i++){
					target [numCaso][i] =  Double.valueOf(st.nextToken()).doubleValue();
				}			
			}
		    
		    in.close();
		} catch (IOException e) {
System.out.println("Error");
		}
		
	}
	public static void main(String [] args)
	{
    		int numNodosEntrada = 3;
    		int numNodosIntermedios = 13;
    		int numNodosSalida = 1;
    		int sizeTrainingSet = 150266;
    		String fileName = "pruebaSBSimplifiedLimitChanged.txt";
    		final int numIteraciones = 500 ;

    		double [][] valoresEntrada = new double [sizeTrainingSet][numNodosEntrada];
    		double [][] target = new double [sizeTrainingSet][numNodosSalida];
    		
    		getTrainingSet(valoresEntrada,target,sizeTrainingSet,numNodosEntrada,numNodosSalida,fileName);
    	
    		RedNeural red = new RedNeural(numNodosEntrada, numNodosIntermedios, numNodosSalida, 0.01);		
            //red = new RedNeural("redNeural.txt");
    		 
            // Entrenarlo
            System.out.println("pruebasSBMerge");  
            for (int i = 0 ; i < numIteraciones; i++){
            	red.resolve_set_cases(valoresEntrada, target, sizeTrainingSet);
            }
    		  
            red.writeToFile("redNeuralSimplified2.txt");
    		
    	}
}
		
		/*
		int numNodosEntrada = 2;
		int numNodosIntermedios = 10;
		int numNodosSalida = 1;
		int sizeTrainingSet = 4;
		
		double [][] valoresEntrada = new double [sizeTrainingSet][numNodosEntrada];
		double [][] target = new double [sizeTrainingSet][numNodosSalida];
		
		valoresEntrada[0][0] = 0;
		valoresEntrada[1][0] = 0;
		valoresEntrada[2][0] = 1;
		valoresEntrada[3][0] = 1;
        
		valoresEntrada[0][1] = 1;
		valoresEntrada[1][1] = 0;
        valoresEntrada[2][1] = 1;
        valoresEntrada[3][1] = 0;
        
        target[0][0] = 1;
        target[1][0] = 0;
        target[2][0] = 1;
        target[3][0] = 0;
        
        final int numIteraciones = 100000;
        
        RedNeural red = new RedNeural(numNodosEntrada,numNodosIntermedios,numNodosSalida,0.01);
        
        // Entrenarlo
        
        for (int i = 0 ; i < numIteraciones; i++){
        	red.resolve_set_cases(valoresEntrada, target, sizeTrainingSet);
        }
        
        // Probarlo
        
        for (int i = 0 ; i < 4; i++){
        	System.out.println(red.calcularSalida(valoresEntrada[i])[0]);
        }
        
        red.writeToFile("redNeural.txt");
		RedNeural red = new RedNeural("redNeural.txt");
		red.writeToFile("redNeural2.txt");
	}
}
        	/*
        	if (red.calcularSalida(entradaX[i], entradaY[i])== target[i]){
        		System.out.println("Correcto");
        	} else{
        		System.out.println("Inorrecto");
        	}
        }
	}
}

*/
