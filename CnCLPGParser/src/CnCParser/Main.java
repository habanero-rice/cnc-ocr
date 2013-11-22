/**
 * This file is part of the CNC-C implementation and
 * distributed under the Modified BSD License. 
 * See LICENSE for details.
 */

package CnCParser;
import CnCParser.Ast.*;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Option option = new Option(args);
            CncLexer Cnc_lexer = new CncLexer(option.getFileName()); // Create the lexer
            CncParser Cnc_parser = new CncParser(Cnc_lexer.getILexStream()); // Create the parser
            
            Cnc_lexer.lexer(Cnc_parser.getIPrsStream()); // Lex the stream to produce the token stream
            if (option.dumpTokens())
            {
                System.out.println("\n****Output Tokens: \n");
                Cnc_parser.getIPrsStream().dumpTokens();
            }
            
            Ast ast = Cnc_parser.parser(); // Parse the token stream to produce an AST
            if (ast == null) 
                System.out.println("****Failure");
            else
            {
                ast.accept(new CncHcGenerator(option.getFileName(), option.getDirName(), option.fullAuto()));
            }

            return;
        }
        catch (Exception e)
        {
            System.err.println(e.getMessage());
            e.printStackTrace();
        }
    }
}