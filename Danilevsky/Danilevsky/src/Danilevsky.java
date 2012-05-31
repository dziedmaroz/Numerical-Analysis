import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;


public class Danilevsky {
    
    private double[][] matrix;       
    public Danilevsky(String filename) throws IOException
    {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        int dim = Integer.parseInt(br.readLine());
        matrix = new double[dim][dim];
        for (int i = 0; i < dim; i++)
        {
            StringTokenizer tmp = new StringTokenizer(br.readLine());
            for (int j = 0; j < dim; j++)
            {
                matrix[i][j] = Double.parseDouble(tmp.nextToken());
            }
        }
    }
    
    double [][] mulMatrix (double [][] A, double [][] B)
    {
	double [][] C = new double [A.length][A.length];
	for (int i=0;i<C.length;i++)
	{
	    for (int j=0;j<C.length;j++)
	    {
		for (int k=0;k<C.length;k++)
		{
		    C[i][j] += A[i][k]*B[k][j];
		}
	    }
	}
	return C;	
    }
    
    private double [][] getSkInv (double [][] A, int k)
    {
	double [][] Sk = new double [A.length][A.length];
	for (int i=0;i<A.length;i++)
	{
	    Sk[i][i]=1;
	}
	for (int i=0;i<A.length;i++)
	{
	    Sk[k][i]=A[k+1][i];
	}
	return Sk;	   
    }
    
    private double [][] getSk (double [][]A, int k)
    {
	double [][]Sk = new double [A.length][A.length];
	for (int i=0;i<A.length;i++)
	{
	    Sk[i][i]=1;
	}
	for (int i=0;i<A.length;i++)
	{
	    Sk[k][i]=(i==k?1:-A[k+1][i])/A[k+1][k];
	}
	return Sk;
    }
    
    private double [][] makePhrobenius ()
    {
	double [][] phrobenius = new double [matrix.length][matrix.length];
	for (int i=0;i<matrix.length;i++)
	{
	    for (int j=0;j<matrix.length;j++)
		phrobenius[i][j]=matrix[i][j];
	}
	for (int i=0;i<phrobenius.length-1;i++)
	{
	    double [][] SkInv = getSkInv(phrobenius, phrobenius.length-2-i);	    
	    double [][] Sk = getSk (phrobenius,phrobenius.length-2-i);	     
	    phrobenius = mulMatrix(SkInv,mulMatrix(phrobenius, Sk));
	}
	return phrobenius;
    }
    
    public double [] getPoly ()
    {
	double [] poly = new double [matrix.length+1];
	poly[0]=1;
	double [][] phrobenius = makePhrobenius();
	for (int i=0;i<matrix.length;i++)
	{
	    poly[i+1] = -1*phrobenius[0][i];
	}
	return poly;
    }
    
}
