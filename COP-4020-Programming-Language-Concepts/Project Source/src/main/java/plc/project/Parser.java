package plc.project;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

/**
 * The parser takes the sequence of tokens emitted by the lexer and turns that
 * into a structured representation of the program, called the Abstract Syntax
 * Tree (AST).
 *
 * The parser has a similar architecture to the lexer, just with {@link Token}s
 * instead of characters. As before, {@link #peek(Object...)} and {@link
 * #match(Object...)} are helpers to make the implementation easier.
 *
 * This type of parser is called <em>recursive descent</em>. Each rule in our
 * grammar will have it's own function, and reference to other rules correspond
 * to calling that functions.
 */
public final class Parser {

    private final TokenStream tokens;

    public Parser(List<Token> tokens) {
        this.tokens = new TokenStream(tokens);
    }

    /**
     * Parses the {@code source} rule.
     */
    public Ast.Source parseSource() throws ParseException {
        Optional<Ast.Expr> val = Optional.empty();

        List<Ast.Field> f = new ArrayList<Ast.Field>();
        List<Ast.Method> m = new ArrayList<Ast.Method>();


        while (tokens.has(0)) {
            if (peek("LET")) {
                f.add(parseField());
            }

            if (peek("DEF")) {
                m.add(parseMethod());
            }
            else {
                //parseStatement();
            }
            tokens.advance();
        }

        Ast.Source as =  new Ast.Source(f, m);

        return as;

    }

    /**
     * Parses the {@code field} rule. This method should only be called if the
     * next tokens start a field, aka {@code LET}.
     */
    public Ast.Field parseField() throws ParseException {
        String name, typeName = "Any";
        Optional<Ast.Expr> value = Optional.empty();
        Token myToken = tokens.get(0);
        tokens.advance();

        if (!peek(Token.Type.IDENTIFIER)) {
            throw new ParseException("Identifier Must Follow", myToken.getIndex());
        }

        name = tokens.get(0).getLiteral();
        myToken = tokens.get(0);
        tokens.advance();
        if(!tokens.has(0)){
            throw new ParseException("Incomplete field, expected an identifier after LET", myToken.getIndex());
        }
        if (peek(";")) {
            return new Ast.Field(name, value);
        }
        else if (!match("=")) {
            if (!peek(":")) {
                throw new ParseException("Field Error - Incorrect Assignment", tokens.get(0).getIndex());
            }
        }

        if (!match(":")) {
            value = Optional.ofNullable(parseExpression());
        }
        else {
            typeName = tokens.get(0).getLiteral();
            tokens.advance();
            if (match("=")) {
                value = Optional.ofNullable(parseExpression());
            }
        }

        if (!match(";")) {
            throw new ParseException("Field Error - Must End with Semicolon", tokens.get(0).getIndex());
        }

        return new Ast.Field(name, typeName, value);
    }

    /**
     * Parses the {@code method} rule. This method should only be called if the
     * next tokens start a method, aka {@code DEF}.
     */
    public Ast.Method parseMethod() throws ParseException {
        Token myToken = tokens.get(0);
        Optional<String> returnTypeName = Optional.of("Any");
        List<String> parameterTypeNames = new ArrayList<>();
        tokens.advance();
        List<String> parameters = new ArrayList<>();
        List<Ast.Stmt> statements = new ArrayList<>();
        if(!tokens.has(0)){
            throw new ParseException("Incomplete method, expected an identifier after DEF", myToken.getIndex());
        }
        String name = tokens.get(0).getLiteral();
        myToken = tokens.get(0);
        if (!match(Token.Type.IDENTIFIER)) {
            throw new ParseException("Incorrect Method - Identifier must follow", tokens.get(0).getIndex());
        }
        if(!tokens.has(0)){
            throw new ParseException("Incomplete method, no left parenthesis", myToken.getIndex());
        }
        myToken = tokens.get(0);
        if (!match("(")) {
            throw new ParseException("Incorrect Method - Must include left paren", tokens.get(0).getIndex());
        }
        else if(!tokens.has(0)){
            throw new ParseException("Incomplete method, no right paren", myToken.getIndex());
        }
        myToken = tokens.get(0);

        if (match(Token.Type.IDENTIFIER)) {
            if(!tokens.has(0)){
                throw new ParseException("Incomplete method, no right paren", myToken.getIndex());
            }
            myToken = tokens.get(0);
            while(match(",")) {
                if(!tokens.has(0)){
                    throw new ParseException("Incomplete method, missing right paren", myToken.getIndex());
                }
                myToken = tokens.get(0);
                if (!peek(Token.Type.IDENTIFIER)) {
                    throw new ParseException("Incorrect Method - Identifier must follow comma", tokens.get(0).getIndex());
                }
                parameters.add(tokens.get(0).getLiteral());
                tokens.advance();
            }
        }

        if (!match(")")) {
            throw new ParseException("Incorrect Method - Must include right paren", tokens.get(0).getIndex());
        }
        if (!tokens.has(0)){
            throw new ParseException("Incomplete method, DO must follow", myToken.getIndex());
        }
        myToken = tokens.get(0);

        if (match(":")) {
            returnTypeName = Optional.of(tokens.get(0).getLiteral());
            tokens.advance();
        }

        if (!match("DO")) {
            throw new ParseException("Incorrect Method - DO must follow", tokens.get(0).getIndex());
        }
        if(!tokens.has(0)){
            throw new ParseException("Incomplete method, END or statement must follow", myToken.getIndex());
        }
        myToken = tokens.get(0);

        while (!match("END")) {
            if(!tokens.has(0)){
                throw new ParseException("Incomplete method, expected END", myToken.getIndex());
            }
            myToken = tokens.get(0);
            statements.add(parseStatement());

        }

        return new Ast.Method(name, parameters, parameterTypeNames, returnTypeName, statements);
    }

    /**
     * Parses the {@code statement} rule and delegates to the necessary method.
     * If the next tokens do not start a declaration, if, while, or return
     * statement, then it is an expression/assignment statement.
     */
    public Ast.Stmt parseStatement() throws ParseException {
        Ast.Stmt statement = null;
        // List<Ast.Stmt.Expression> assign = new ArrayList<>();
        Token myToken = tokens.get(0);

        if (peek("IF")) {
            statement = parseIfStatement();
        }
        else if (peek("FOR")) {
            statement = parseForStatement();
        }
        else if (peek("WHILE")) {
            statement = parseWhileStatement();
        }
        else if (peek("LET")) {
            Ast.Field f = parseField();
            if (f.getTypeName().equals("Any")) {
                return new Ast.Stmt.Declaration(f.getName(), f.getValue());
            }
            return new Ast.Stmt.Declaration(f.getName(), Optional.of(f.getTypeName()), f.getValue());
        }
        else if (peek("RETURN")) {
            statement = parseReturnStatement();
        }
        else {
            Ast.Stmt.Expression receiver = new Ast.Stmt.Expression(parseExpression());
            if (!tokens.has(0)) {
                throw new ParseException("Incomplete statement, expected semicolon ;", myToken.getIndex());
            }
            myToken = tokens.get(0);
            if (match("=")) {
                if (!tokens.has(0)) {
                    throw new ParseException("Incomplete statement, expected equal sign =", myToken.getIndex());
                }
                myToken = tokens.get(0);
                Ast.Stmt.Expression value = new Ast.Stmt.Expression(parseExpression());
                if (!tokens.has(0)) {
                    throw new ParseException("Incomplete statement, expected semicolon ;", myToken.getIndex());
                }
                myToken = tokens.get(0);
                if (!match(";")) {
                    throw new ParseException("Incomplete assignment statement, missing semicolon ;", myToken.getIndex());
                }
                return new Ast.Stmt.Assignment(receiver.getExpression(), value.getExpression());
                //throw new ParseException("Incorrect Assignment - Equals must follow", tokens.index);
            }
            if (!match(";")) {
                throw new ParseException("Incomplete assignment statement, missing semicolon ;", myToken.getIndex());
            }
            else {
                return new Ast.Stmt.Expression(receiver.getExpression());
            }
        }
        return statement;

        //throw new UnsupportedOperationException(); //TODO
    }

    /**
     * Parses a declaration statement from the {@code statement} rule. This
     * method should only be called if the next tokens start a declaration
     * statement, aka {@code LET}.
     */
    public Ast.Stmt.Declaration parseDeclarationStatement() throws ParseException {
        Ast.Field f = parseField();
        return new Ast.Stmt.Declaration(f.getName(), f.getValue());
    }

    /**
     * Parses an if statement from the {@code statement} rule. This method
     * should only be called if the next tokens start an if statement, aka
     * {@code IF}.
     */
    public Ast.Stmt.If parseIfStatement() throws ParseException {
        Ast.Expr exprCondition = null;
        List<Ast.Stmt> thenStatements = new ArrayList<>();
        List<Ast.Stmt> elseStatements = new ArrayList<>();
        Token myToken = tokens.get(0);

        tokens.advance();
        exprCondition = parseExpression();

        if (!match("DO")) {
            throw new ParseException("Incorrect If Statement - DO must follow", tokens.get(0).getIndex());
        }

        if (!tokens.has(0)) {
            throw new ParseException("Incomplete IF statement, expected END", myToken.getIndex());
        }
        myToken = tokens.get(0);

        while (!peek("END")) {
            if (peek("ELSE")) {
                tokens.advance();
                break;
            }
            else {
                thenStatements.add(parseStatement());
                if (!tokens.has(0)) {
                    throw new ParseException("Incomplete IF statement, expected END", myToken.getIndex());
                }
                myToken = tokens.get(0);
//                if (peek(";")) {
//                    tokens.advance();
//                }
            }
            if (!tokens.has(0)) {
                throw new ParseException("Incomplete IF statement, expected END", myToken.getIndex());
            }
            myToken = tokens.get(0);
        }
        while (!match("END")) {
            elseStatements.add(parseStatement());
            if (!tokens.has(0)) {
                throw new ParseException("Incomplete IF statement, expected END", myToken.getIndex());
            }
            myToken = tokens.get(0);
//            if (peek(";")) {
//                tokens.advance();
//            }
        }

        return new Ast.Stmt.If(exprCondition, thenStatements, elseStatements);
    }

    /**
     * Parses a for statement from the {@code statement} rule. This method
     * should only be called if the next tokens start a for statement, aka
     * {@code FOR}.
     */
    public Ast.Stmt.For parseForStatement() throws ParseException {
        Ast.Expr exprValue;
        List<Ast.Stmt> statements = new ArrayList<>();
        Token myToken = tokens.get(0);

        tokens.advance();
        if (!tokens.has(0)) {
            throw new ParseException("Incomplete FOR statement, expected identifier", myToken.getIndex());
        }
        myToken = tokens.get(0);
        String name = myToken.getLiteral();

        if (!match(Token.Type.IDENTIFIER)) {
            throw new ParseException("Incorrect FOR Statement - IDENTIFIER must follow", tokens.get(0).getIndex());
        }

        if (!tokens.has(0)) {
            throw new ParseException("Incomplete FOR statement, expected IN", myToken.getIndex());
        }
        myToken = tokens.get(0);

        if (!match("IN")) {
            throw new ParseException("Incorrect FOR Statement - IN must follow", tokens.get(0).getIndex());
        }

        if (!tokens.has(0)) {
            throw new ParseException("Incomplete FOR statement, expected expression", myToken.getIndex());
        }
        myToken = tokens.get(0);

        exprValue = parseExpression();

        if (!tokens.has(0)) {
            throw new ParseException("Incomplete IF statement, expected DO", myToken.getIndex());
        }
        myToken = tokens.get(0);

        if (!match("DO")) {
            throw new ParseException("Incorrect FOR Statement - DO must follow", tokens.get(0).getIndex());
        }

        if (!tokens.has(0)) {
            throw new ParseException("Incomplete IF statement, expected statement", myToken.getIndex());
        }
        myToken = tokens.get(0);

        while (!match("END")) {
            statements.add(parseStatement());
            myToken = tokens.get(0);
        }

        return new Ast.Stmt.For(name, exprValue, statements);
    }

    /**
     * Parses a while statement from the {@code statement} rule. This method
     * should only be called if the next tokens start a while statement, aka
     * {@code WHILE}.
     */
    public Ast.Stmt.While parseWhileStatement() throws ParseException {
        Ast.Expr exprCondition;
        List<Ast.Stmt> statements = new ArrayList<>();
        Token myToken = tokens.get(0);

        tokens.advance();
        if (!tokens.has(0)) {
            throw new ParseException("Incomplete WHILE statement, expected conditional expression", myToken.getIndex());
        }
        myToken = tokens.get(0);

        exprCondition = parseExpression();

        myToken = tokens.get(0);

        if (!match("DO")) {
            throw new ParseException("Incorrect WHILE Statement - DO must follow", tokens.get(0).getIndex());
        }

        if (!tokens.has(0)) {
            throw new ParseException("Incomplete WHILE statement, expected statement", myToken.getIndex());
        }
        myToken = tokens.get(0);

        while (!match("END")) {
            statements.add(parseStatement());
            myToken = tokens.get(0);
        }

        return new Ast.Stmt.While(exprCondition, statements);
    }

    /**
     * Parses a return statement from the {@code statement} rule. This method
     * should only be called if the next tokens start a return statement, aka
     * {@code RETURN}.
     */
    public Ast.Stmt.Return parseReturnStatement() throws ParseException {
        Token myToken = tokens.get(0);

        tokens.advance();
        if (!tokens.has(0)) {
            throw new ParseException("Incomplete RETURN statement, expected expression", myToken.getIndex());
        }
        myToken = tokens.get(0);

        Ast.Expr value = parseExpression();

        if (!tokens.has(0)) {
            throw new ParseException("Incomplete RETURN statement - must end with a semicolon", myToken.getIndex());
        }
        myToken = tokens.get(0);

        if (!match(";")) {
            throw new ParseException("Incorrect RETURN Statement - expected a semicolon", tokens.get(0).getIndex());
        }

        return new Ast.Stmt.Return(value);
        //throw new UnsupportedOperationException(); //TODO
    }

    /**
     * Parses the {@code expression} rule.
     */
    public Ast.Expr parseExpression() throws ParseException {
        return parseLogicalExpression();
    }

    /**
     * Parses the {@code logical-expression} rule.
     */
    public Ast.Expr parseLogicalExpression() throws ParseException {
        Ast.Expr lhs = parseEqualityExpression();
        Ast.Expr rhs;
        Token myToken;
        if(tokens.has(0)){
            myToken = tokens.get(0);
            if (peek("AND")||peek("OR")) {
                tokens.advance();
                if(!tokens.has(0)){
                    throw new ParseException("Incorrect Logical Expression", myToken.getIndex());
                }
                rhs = parseLogicalExpression();
                return new Ast.Expr.Binary(myToken.getLiteral(),lhs,rhs);
            }

        }
        return lhs;
    }

    /**
     * Parses the {@code equality-expression} rule.
     */
    public Ast.Expr parseEqualityExpression() throws ParseException {
        Ast.Expr lhs = parseAdditiveExpression();
        Ast.Expr rhs;
        Token myToken;
        if(tokens.has(0)){
            myToken = tokens.get(0);
            if (peek("!=") || peek("==") || peek(">=") || peek("<=") || peek("<") || peek(">")) {
                tokens.advance();
                if(!tokens.has(0)){
                    throw new ParseException("Incorrect Comparison Expression", myToken.getIndex());
                }
                rhs = parseEqualityExpression();
                return new Ast.Expr.Binary(myToken.getLiteral(),lhs,rhs);
            }

        }
        return lhs;

    }


    /**
     * Parses the {@code additive-expression} rule.
     */
    public Ast.Expr parseAdditiveExpression() throws ParseException {
        Ast.Expr lhs = parseMultiplicativeExpression();
        Ast.Expr rhs;
        Token myToken;
        if(tokens.has(0)){
            myToken = tokens.get(0);
            if (peek("-") || peek("+")) {
                tokens.advance();
                if(!tokens.has(0)){
                    throw new ParseException("Incorrect Additive Expression", myToken.getIndex());
                }
                rhs = parseAdditiveExpression();
                return new Ast.Expr.Binary(myToken.getLiteral(),lhs,rhs);
            }

        }
        return lhs;

    }

    /**
     * Parses the {@code multiplicative-expression} rule.
     */
    public Ast.Expr parseMultiplicativeExpression() throws ParseException {
        Ast.Expr lhs = parseSecondaryExpression();
        Ast.Expr rhs;
        Token myToken;
        if(tokens.has(0)){
            myToken = tokens.get(0);
            if (peek("/") || peek("*")) {
                tokens.advance();
                if(!tokens.has(0)){
                    throw new ParseException("Incorrect Multiplicative Expression", myToken.getIndex());
                }
                rhs = parseMultiplicativeExpression();
                return new Ast.Expr.Binary(myToken.getLiteral(),lhs,rhs);
            }
        }
        return lhs;

    }

    /**
     * Parses the {@code secondary-expression} rule.
     */
    public Ast.Expr parseSecondaryExpression() throws ParseException {
        Ast.Expr expr = parsePrimaryExpression();
        Optional<Ast.Expr> receiver = Optional.empty();
        if(peek(".")){
            receiver = Optional.of(expr);
        }
        while (match(".")) {
            int start = tokens.get(0).getIndex();
            List<Ast.Expr> exprList = new ArrayList<>();
            if(!tokens.has(0)){
                throw new ParseException("Trailing '.', invalid function",start+1);
            }
            Token myToken = tokens.get(0);
            String myStr = myToken.getLiteral();
            Token errToken = myToken;
            if(match(Token.Type.IDENTIFIER)){
                if(peek("(")){
                    errToken = tokens.get(0);
                    tokens.advance();
                    if(!tokens.has(0)){
                        throw new ParseException("Incomplete function, missing ')'", myToken.getIndex());
                    }
                    if(match(")")){//No arguments
                        if(peek(".")) {
                            receiver = Optional.of(new Ast.Expr.Function(receiver, myStr, exprList));
                        }
                        else {
                            return new Ast.Expr.Function(receiver,myStr,exprList);
                        }
                    }
                    else{
                        exprList.add(parseExpression());//Get first argument
                        while(!match(")")){//repeat until ')" is found or error occurs
                            if(!tokens.has(0)){
                                errToken = tokens.get(0);
                                throw new ParseException("Function missing right parenthesis", errToken.getIndex());
                            }
                            if(!match(",")){
                                errToken = tokens.get(0);
                                throw new ParseException("Missing Comma in function arguments",errToken.getIndex());
                            }
                            exprList.add(parseExpression());
                        }
                        if(peek(".")){
                            receiver = Optional.of(new Ast.Expr.Function(receiver,myStr,exprList));
                        }
                        else{
                            return new Ast.Expr.Function(receiver,myStr,exprList);
                        }
                    }
                    exprList.clear();
                }
                else if(!peek(".")) {
                    //If there is no dot, then we count it as an Access object
                    return new Ast.Expr.Access(receiver, myStr);
                }
            }
            else{
                throw new ParseException("Invalid identifier for function or variable",myToken.getIndex());
            }
        }
        return expr;
    }

    /**
     * Parses the {@code primary-expression} rule. This is the top-level rule
     * for expressions and includes literal values, grouping, variables, and
     * functions. It may be helpful to break these up into other methods but is
     * not strictly necessary.
     */
    public Ast.Expr parsePrimaryExpression() throws ParseException {
        //Literal = NIL, TRUE, FALSE, integer, decimal, character, string
        Token myToken = tokens.get(0);
        boolean t = true;
        boolean f = false;
        myToken = tokens.get(0);
        String myStr = myToken.getLiteral();
        if(peek("NIL")){
            if(tokens.has(1)){
                tokens.advance();
            }
            return new Ast.Expr.Literal(null);
        }
        else if(peek("TRUE")){
            if(tokens.has(1)){
                tokens.advance();
            }
            return new Ast.Expr.Literal(t);
        }
        else if(peek("FALSE")){
            if(tokens.has(1)){
                tokens.advance();
            }
            return new Ast.Expr.Literal(f);
        }
        else if(peek(Token.Type.INTEGER)){
            if(tokens.has(1)){
                tokens.advance();
            }
            BigInteger myNum = new BigInteger(myStr);
            return new Ast.Expr.Literal(myNum);
        }
        else if(peek(Token.Type.DECIMAL)){
            if(tokens.has(1)){
                tokens.advance();
            }
            BigDecimal myDec = new BigDecimal(myStr);
            return new Ast.Expr.Literal(myDec);
        }
        else if(peek(Token.Type.CHARACTER)){
            if(tokens.has(1)){
                tokens.advance();
            }
            return new Ast.Expr.Literal(myStr.charAt(1));
        }
        else if(peek(Token.Type.STRING)){
            if(tokens.has(1)){
                tokens.advance();
            }
            myStr =  myStr.replaceAll("\\\\b", "\b").
                    replaceAll("\\\\n", "\n").
                    replaceAll("\\\\r", "\r").
                    replaceAll("\\\\t", "\t");
            return new Ast.Expr.Literal(myStr.substring(1, myStr.length() - 1).replaceAll("\"", ""));
            //return new Ast.Expr.Literal(myStr.substring(1, myStr.length() - 1).replaceAll("\\\\","\\"));
        }
        //Grouping: <operator(> <expression> <operator)>
        else if(peek(Token.Type.OPERATOR)){
            if(myStr.contains("(")){
                tokens.advance();
                if(!tokens.has(0)){
                    throw new ParseException("Incomplete Group, Missing ')'",myToken.getIndex());
                }
                Ast.Expr exprGroup = parseExpression();//recursive
                if(match(")")){
                    return new Ast.Expr.Group(exprGroup);
                }
                else{
                    throw new ParseException("Incomplete Group, Missing ')'",myToken.getIndex());
                }
            }
            else{ //first operator is not a left parenthesis
                throw new ParseException("Invalid leading operator",myToken.getIndex());
            }
        }
        //Function: identifier ('(' (expression (',' expression)*)? ')')?
        else if(peek(Token.Type.IDENTIFIER)){
            Optional<Ast.Expr> receiver = Optional.empty();
            if (tokens.has(1)) {
                if (tokens.get(1).getLiteral().equals("(")) {
                    tokens.advance();
                }
            }
            if(peek("(")){
                tokens.advance();
                if(!tokens.has(0)){
                    throw new ParseException("Incomplete function, missing ')'", myToken.getIndex());
                }
                List<Ast.Expr> exprList = new ArrayList<>();
                if(match(")")){//No arguments
                    return new Ast.Expr.Function(receiver,myStr,exprList);
                }
                else{
                    exprList.add(parseExpression());//Get first argument
                    while(!match(")")){//repeat until ')" is found or error occurs
                        if(!tokens.has(0)){
                            throw new ParseException("Function missing right parenthesis",myToken.getIndex());
                        }
                        if(!match(",")){
                            throw new ParseException("Missing Comma in function arguments",myToken.getIndex());
                        }
                        exprList.add(parseExpression());
                    }
                }
                return new Ast.Expr.Function(receiver,myStr,exprList);
            }
            //If there are no parentheses after the identifier, then it is an Access object
            tokens.advance();
            return new Ast.Expr.Access(receiver,myStr);
        }
        else{
            throw new AssertionError("No expression found");
        }
    }

    /**
     * As in the lexer, returns {@code true} if the current sequence of tokens
     * matches the given patterns. Unlike the lexer, the pattern is not a regex;
     * instead it is either a {@link Token.Type}, which matches if the token's
     * type is the same, or a {@link String}, which matches if the token's
     * literal is the same.
     *
     * In other words, {@code Token(IDENTIFIER, "literal")} is matched by both
     * {@code peek(Token.Type.IDENTIFIER)} and {@code peek("literal")}.
     */
    private boolean peek(Object... patterns) {
        for(int i = 0; i < patterns.length; i++){
            if(!tokens.has(i)) {
                return false;
            }
            else if(patterns[i] instanceof Token.Type){
                if(patterns[i]!=tokens.get(i).getType()){
                    return false;
                }
            }
            else if(patterns[i] instanceof String){
                if(!patterns[i].equals(tokens.get(i).getLiteral())){
                    return false;
                }
            }
            else{
                throw new AssertionError("Invalid pattern object: "+patterns[i].getClass());
            }
        }
        return true;
    }


    /**
     * As in the lexer, returns {@code true} if {@link #peek(Object...)} is true
     * and advances the token stream.
     */
    private boolean match(Object... patterns) {
        boolean peek = peek(patterns);
        if(peek){
            for(int i = 0; i < patterns.length; i++){
                tokens.advance();
            }
        }
        return peek;
    }

    private static final class TokenStream {

        private final List<Token> tokens;
        private int index = 0;

        private TokenStream(List<Token> tokens) {
            this.tokens = tokens;
        }

        /**
         * Returns true if there is a token at index + offset.
         */
        public boolean has(int offset) {
            return index + offset < tokens.size();
        }

        /**
         * Gets the token at index + offset.
         */
        public Token get(int offset) {
            return tokens.get(index + offset);
        }

        /**
         * Advances to the next token, incrementing the index.
         */
        public void advance() {
            index++;
        }

    }

}
