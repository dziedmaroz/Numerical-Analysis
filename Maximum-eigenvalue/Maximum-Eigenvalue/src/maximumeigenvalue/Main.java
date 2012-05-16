/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package maximumeigenvalue;

import java.io.IOException;

/**
 *
 * @author lucian
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       try
       {
            MaximumEgien maximumEgien = new MaximumEgien(args[0]);
            System.out.println(maximumEgien.getMaxEigen());
        }
       catch (IOException e)
       {
           e.printStackTrace();
       }

    }

}
