import java.io.IOException;


public class Main {

    /**
     * @param args
     */
    public static void main(String[] args) {
	 try
	       {
	            Danilevsky danilevsky = new Danilevsky(args[0]);	             
		    
	            double [] poly = danilevsky.getPoly();
	            for (int i=0;i<poly.length;i++)
	            {
	        	System.out.printf ("%-8.3f\t",poly[i]);
	            }
	        }
	       catch (IOException e)
	       {
	           e.printStackTrace();
	       }

    }

}
