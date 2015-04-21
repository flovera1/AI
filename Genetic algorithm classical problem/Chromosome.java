/**
* Genetic Algorithm Node
*/
import java.util.*;	
	public class Chromosome {
		// The chromo
		static int chromoLen             = 5;
		static Random rand               = new Random();
		static double crossRate          = 0.7;
		static double mutRate            = 0.001;
		static char[] ltable             = {'0','1','2','3','4','5','6','7','8','9','+','-','*','/'};
		StringBuffer chromo		         = new StringBuffer(chromoLen * 4);
		public StringBuffer decodeChromo = new StringBuffer(chromoLen * 4);
		public double score              = 0.0;
		public int total                 = 0;
		public Chromosome(){};
		/**
		* @desc: Constructor that generates a random Chromosome
		*/
		public Chromosome(int target) {
			// Create the full buffer
			for(int y = 0; y < chromoLen; y++) {
				// Generate a random binary integer
				String binString = Integer.toBinaryString(rand.nextInt(ltable.length));
				int fillLen      = 4 - binString.length();
				// Fill to 4
				for (int x = 0; x < fillLen; x++){ 
					chromo.append('0');
				}
				// Append the chromo
				chromo.append(binString);
			}
			// Score the new cromo
			scoreChromo(target);
		}				
		public Chromosome(StringBuffer chromo) { 
			this.chromo = chromo; 
		}
		// Decode the string
		public final String decodeChromo(){
			// Create a buffer
			decodeChromo.setLength(0);
			// Loop throught the chromo
			for (int x = 0; x < chromo.length(); x += 4) {
				// Get the integer representation of the substring with base 2 (radix, 2nd parameter)
				int idx = Integer.parseInt(chromo.substring(x,x+4), 2);// radix is 2 coz we have 0s and 1s
				if (idx < ltable.length) {
					decodeChromo.append(ltable[idx]);
				}
			}
			// Return the string
			return decodeChromo.toString();
		}
		
		// Scores this chromo
		public final void scoreChromo(int target) {
			total = addUp();
			if (total == target) score = 0;
			score = (double)1 / (target - total);
		}
		/**
		* @description: first check if we Should cross over, then, Generate a random position, 
		*               and,Swap all chars after that position.
		* @param other: the other Chromosome to make the crossover
		* @output : void. You just swap values in the chromosomes.
		*/
		public final void crossOver(Chromosome other) {
			if (rand.nextDouble() <= crossRate){ 
				int pos = rand.nextInt(chromo.length());
				for (int x = pos; x < chromo.length(); x++) {
					char tmp = chromo.charAt(x);					
					// Swap
					chromo.setCharAt(x, other.chromo.charAt(x));
					other.chromo.setCharAt(x, tmp);
				}
			}
		}
		/**
		* @description: when you are mutating, then what is going to happen is that you are going to change
		*   	 	 	'0s' for '1s' and '1s' for '0s' from one point forward in the chromosome.
		* @param: void
		* @output: void. You just change the bits
		*
		*/
		public final void mutate() {
			for (int x = 0; x < chromo.length(); x++) {
				if (rand.nextDouble() <= mutRate){ 
					chromo.setCharAt(x, (chromo.charAt(x)=='0' ? '1' : '0'));
				}
			}
		}		
		/**
		* @description: basically when you have something in the decoded mode, for example:
		*     	 	 	decoded = '6+5'
		*  	  	  	  	what's going to happen is that addUp will scan that string and add the content
		* 	  	  	 	or subtract, multiply, or divide (depending on the operation), this is made
		*   	 	  	by putting the int value in the variable tot and using ptr to move forward in the
		*    	 	  	string, checking if the char is an operator(save the operator in variable var)
		* 	 	 	 	or a number (doing the switch case).
		*/		
		public final int addUp() { 
			String decodedString = decodeChromo();
			int tot              = 0;	
			int ptr              = 0;//find the number
			while (ptr < decodedString.length()) { 
				char ch = decodedString.charAt(ptr);
				if (Character.isDigit(ch)) {
					tot = ch-'0';
					ptr++;
					break;
				} else {
					ptr++;
				}
			}
			// If no numbers found, return
			if (ptr == decodedString.length()){
			 return 0;
		 	}
			// Loop processing the rest
			boolean num = false;
			char oper   = ' ';
			while (ptr < decodedString.length()) {
				// Get the character
				char ch = decodedString.charAt(ptr);
				// Is it what we expect, if not - skip
				if (num && !Character.isDigit(ch)) {
					ptr++;
					continue;
				}
				if (!num && Character.isDigit(ch)) {
					ptr++;
					continue;
				}
				// Is it a number
				if (num) { 
					switch (oper) {
						case '+' : { tot+=(ch-'0'); break; }
						case '-' : { tot-=(ch-'0'); break; }
						case '*' : { tot*=(ch-'0'); break; }
						case '/' : { if (ch!='0') tot/=(ch-'0'); break; }
					}
				} else {
					oper = ch;
				}			
				// Go to next character
				ptr++;
				num=!num;
			}
			return tot;
		}
		/**
		* @description: isValid proves that the pattern number - operator - number - operator - number and
		*   	 	 	so on, is followed.
		* @return: True if the pattern was followed.
		*  	  	   False otherwise.
		* @param: void.
		*/
		public final boolean isValid() { 
			// Decode our chromo
			String decodedString = decodeChromo();	
			boolean num          = true; // it has the value true when the character is a number.
			for (int x = 0; x < decodedString.length(); x++) {
				char ch = decodedString.charAt(x);
				// Did we follow the num-oper-num-oper-num patter
				if (num == !Character.isDigit(ch)) return false;// if the first character is not a number
				// Don't allow divide by zero
				if (x>0 && ch=='0' && decodedString.charAt(x-1)=='/') return false;
				num =! num;
			}
			// Can't end in an operator
			if (!Character.isDigit(decodedString.charAt(decodedString.length()-1))) return false;
			return true;
		}
}