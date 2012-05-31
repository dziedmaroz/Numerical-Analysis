 

import java.io.IOException;

import org.junit.Test;

/**
 * 
 */

/**
 * @author lucian
 *
 */
public class DanilevskyTest   {

    @Test
    public void test() {
	try
	{
	    Danilevsky danilevsky = new Danilevsky("input.txt");
	    double [][] A = new double [4][4];
	    for (int i=0;i<4;i++)
	    {
		
		A[i][i] = 1;
	    }
	    double [][] B = new double [4][4];
	    for (int i=0;i<4;i++)
	    {
		for (int j=0;j<4;j++)
		{
		    B[i][j]=i+j;
		}		
	    }
	    double [][] C = danilevsky.mulMatrix(A, B);
	    for (int i=0;i<4;i++)
	    {
		for (int j=0;j<4;j++)
		{
		    System.out.printf("%3.0\t", C[i][j]);
		}
		System.out.println();
	    }
	}
	catch (IOException e)
	{
	    e.printStackTrace();
	}
	
    }

}
