import java.util.Scanner;

public class GradeCalculator {
    public static void main(String[] args){
    	Scanner input=new Scanner(System.in);
    	System.out.print("Enter the number of students: ");
    	int num=input.nextInt();
    	int[] scores=new int[num];
    	char[] grades=new char[num];
    	   	
    	System.out.print("Enter "+num+" scores: ");
    	
    	int best=-1;
    	for(int i=0;i<num;i++){
    		scores[i]=input.nextInt();
    		if(best<scores[i])
    			best=scores[i];
    	}
    	
    	for(int i=0;i<num;i++) {
			if (scores[i] >= best - 10)
				grades[i] = 'A';
			else if (scores[i] >= best - 20)
				grades[i] = 'B';
			else if (scores[i] >= best - 30)
				grades[i] = 'C';
			else if (scores[i] >= best - 40)
				grades[i] = 'D';
			else grades[i] = 'F';
			
			// What's with (i + 1)? ==> Only programmers count from zero!
			System.out.println("Student " + (i + 1) + " - Score: " + scores[i] + ", Letter: " + grades[i]);
		}
    	
    	input.close();
    }
}
