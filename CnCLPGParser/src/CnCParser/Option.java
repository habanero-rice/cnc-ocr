/**
 * This file is part of the CNC-C implementation and
 * distributed under the Modified BSD License. 
 * See LICENSE for details.
 */

package CnCParser;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Option
{
    String fileName = "input";
    String dir = null;
    boolean dumpTokens = false;
    boolean dumpKeywords = false;
    boolean print  = false;
    boolean fullauto = false;
    char[] inputChars;


    public Option(String [] args)
    {
        for (int i = 0; i < args.length; i++)
        {
            if (args[i].charAt(0) == '-')
            {
                if (args[i].equals("-d"))
                    dumpTokens = true;
                else if (args[i].equals("-k"))
                    dumpKeywords = true;
                else if (args[i].equals("-p"))
                    print = true;
                else if (args[i].equals("-full-auto"))
                    fullauto = true;
                else if (args[i].equals("-dir"))
                    dir = args[++i]+"/"; //linux specific
                else{
                	System.err.println("Unknown option: "+args[i]);
                	Usage();
                	System.exit(1);
                }
            }
            else
            {
                fileName = args[i];
                break;
            }
        }
    }
    
    public void Usage(){
    	System.err.println("Usage:");
    	System.err.println("CnCc [options] filename");
    	System.err.println("Options:");
    	System.err.println("-d: dump parsed tokens");
    	System.err.println("-k: dump keywords");
    	System.err.println("-p: print the AST");
    	System.err.println("-dir: directory for placing generated files");
    	System.err.println("-full-auto: fully automate Main.hc and step stubs for CDSC applications");
    	System.err.println("filename: the source file containing the CnC code");    	
    
    }

    public String getFileName() { return fileName; }

    public String getDirName() { return dir; }
    
    public boolean dumpTokens() { return dumpTokens; }

    public boolean dumpKeywords() { return dumpKeywords; }

    public boolean printTokens() { return print; }
    
    public boolean fullAuto() { return fullauto; }

    public char[] getInputChars() { return inputChars; }

    public int readInputChars() throws IOException
    {
        int rlen = 0;
        try
        {
            // Create a reader for the input stream and read the input file into a char array.
            File f = new File(fileName);
            int len = (int) f.length();
                BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(f)));

            inputChars = new char[len];

            rlen = in.read(inputChars, 0, len);

        }
        catch (Exception e)
        {
            IOException io = new IOException();
            System.err.println(e.getMessage());
            e.printStackTrace();
            throw(io);
        }
        return rlen;
    }
}
