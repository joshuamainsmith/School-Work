package plc.project;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.lang.*; // Added

/**
 * The lexer works through three main functions:
 *
 *  - {@link #lex()}, which repeatedly calls lexToken() and skips whitespace
 *  - {@link #lexToken()}, which lexes the next token
 *  - {@link CharStream}, which manages the state of the lexer and literals
 *
 * If the lexer fails to parse something (such as an unterminated string) you
 * should throw a {@link ParseException} with an index at the character which is
 * invalid or missing.
 *
 * The {@link #peek(String...)} and {@link #match(String...)} functions are
 * helpers you need to use, they will make the implementation a lot easier.
 */
public final class Lexer {

    private final CharStream chars;

    public Lexer(String input) {
        chars = new CharStream(input);
    }

    /**
     * Repeatedly lexes the input using {@link #lexToken()}, also skipping over
     * whitespace where appropriate.
     */
    public List<Token> lex() {
        List<Token> arrToken = new ArrayList<Token>();
        Lexer lex = new Lexer(chars.input);

        while (lex.chars.has(0)) { //if there are chars left in the input string

            //Skip whitespace characters
            if(lex.peek("[ \b\n\r\t]")){
                lex.chars.advance();
                lex.chars.skip(); //Skip the whitespace character and move to the next char in the input string
            }
            else {
                arrToken.add(lexToken(lex));
            }
        }

        return arrToken;
    }

    /**
     * This method determines the type of the next token, delegating to the
     * appropriate lex method. As such, it is best for this method to not change
     * the state of the char stream (thus, use peek not match).
     *
     * The next character should start a valid token since whitespace is handled
     * by {@link #lex()}
     */

    public Token lexToken() {
        Token token = new Token(Token.Type.IDENTIFIER, "", 0);
        Lexer lex = new Lexer(chars.input);

        token = lexToken(lex);

        return token;
    }

    public Token lexToken(Lexer lex) {
        Token token = new Token(Token.Type.IDENTIFIER, "", 0);

        /* integer or decimal */
        if (lex.peek("[+\\-]", "[0-9]") || lex.peek("[0-9]")) {
            token = lexNumber(lex); //lexNumber will decide if the +/- is an operator or not
            return token;
        }
        /* string */
        else if (lex.peek("\\\"")) { //Only strings start with double quotes
            token = lexString(lex); //Reads it as a string until 2nd double quote
            return token;
        }

        /* identifier */
        else if (lex.peek("[A-Za-z_]")) {
            token = lexIdentifier(lex); //These characters can be the start of an identifier
            return token;
        }

        /* escape */
        else if(lex.peek("\\\'")){
            token = lexCharacter(lex); //Checks for one more character and a second single quote
        }
        /* operator */
        else{
            //starting with anything else, it can only be an operator
            token = lexOperator(lex);
        }

        return token;
    }

    public Token lexIdentifier(Lexer lex) {
        while (lex.peek(".")) { // iterate through every character
            if (!lex.peek("[A-Za-z0-9_\\-]")) { // end of identifier
                return lex.chars.emit(Token.Type.IDENTIFIER);
            }
            lex.chars.advance();
        }
        // correct identifier
        return lex.chars.emit(Token.Type.IDENTIFIER);

    }

    public Token lexNumber(Lexer lex) {
        boolean decimal = false;

        if (lex.peek("[+\\-]")) {
            if (!lex.peek("[+\\-]", "[0-9]")) { // Next character not digit, so operator
                return lex.chars.emit(Token.Type.OPERATOR);
            }
            lex.chars.advance();
        }
        while (lex.chars.has(0)) {
            if (lex.peek("\\.")) {
                if (!lex.peek(".", "[0-9]")) { //Trailing decimal not allowed, example: 5.
                    throw new ParseException("Trailing Decimal", lex.chars.index + 1);
                }
                if (!decimal){
                    decimal = true;
                }
                else { // decimal already set to true.
                    throw new ParseException("Multiple Decimals", lex.chars.index + 1);
                }
            }
            else if (!lex.peek("[0-9]")) { // non-digits found
                break;
            }

            lex.chars.advance();
        }

        if (decimal) {
            // decimal
            return lex.chars.emit(Token.Type.DECIMAL);
        }
        else {
            // integer
            return lex.chars.emit(Token.Type.INTEGER);
        }
    }

    public Token lexCharacter(Lexer lex) {
        lex.chars.advance();

        if (lex.match("\\\\")) { // escape character
            lexEscape(lex);
            lex.chars.advance();
        }
        else if (lex.match("'")) { // empty chars not allowed
            throw new ParseException("Empty", lex.chars.index + 1);
        }
        else if (!lex.match(".", "'")) { // only one char allowed between ''
            throw new ParseException("Doesn't Follow Pattern", lex.chars.index + 1);
        }
        return lex.chars.emit(Token.Type.CHARACTER);
    }

    public Token lexString(Lexer lex) {
        lex.chars.advance();
        while (lex.peek(".")) {
            if (!lex.chars.has(1)) { // current char is last
                if (!lex.peek("\"")) { // if last char != " then unterminated string
                    throw new ParseException("Unterminated Quote", lex.chars.index + 1);
                }
            }
            if (lex.peek("\"")) { // end of string found
                lex.chars.advance();
                return lex.chars.emit(Token.Type.STRING);
            }
            else if (lex.match("\\\\")) { // check escape sequence
                lexEscape(lex);
            }
            lex.chars.advance();
        }
        return lex.chars.emit(Token.Type.STRING);
    }

    public void lexEscape(Lexer lex) { //should be called in lexCharacter and lexString to check for valid escapes
        if (!lex.match("[bnrt'\"\\\\]")) { // incorrect escape sequence
            throw new ParseException("Incorrect Escape", lex.chars.index);
        }
    }

    public Token lexOperator(Lexer lex) {
        if (lex.match("[<>!=]")) { // special operator
            if (lex.match("=")) { // If next char =, then treat as single token
                return lex.chars.emit(Token.Type.OPERATOR);
            }
        }
        else {
            lex.chars.advance();
        }
        return lex.chars.emit(Token.Type.OPERATOR);
    }

    /**
     * Returns true if the next sequence of characters match the given patterns,
     * which should be a regex. For example, {@code peek("a", "b", "c")} would
     * return true if the next characters are {@code 'a', 'b', 'c'}.
     */
    public boolean peek(String... patterns) { // returns boolean on pattern match
        for (int i = 0; i < patterns.length; i++) {
            if (!chars.has(i) || !String.valueOf(chars.get(i)).matches(patterns[i])){
                return false;
            }
        }
        return true;
    }

    /**
     * Returns true in the same way as {@link #peek(String...)}, but also
     * advances the character stream past all matched characters if peek returns
     * true. Hint - it's easiest to have this method simply call peek.
     */
    public boolean match(String... patterns) { // calls peek, then advances if peek == true
        boolean peek = peek(patterns);
        if (peek) {
            for (int i = 0; i < patterns.length; i++) {
                chars.advance();
            }
        }
        return peek;
    }

    /**
     * A helper class maintaining the input string, current index of the char
     * stream, and the current length of the token being matched.
     *
     * You should rely on peek/match for state management in nearly all cases.
     * The only field you need to access is {@link #index} for any {@link
     * ParseException} which is thrown.
     */
    public static final class CharStream {

        private final String input;
        private int index = 0;
        private int length = 0;

        public CharStream(String input) {
            this.input = input;
        }

        public boolean has(int offset) {
            return index + offset < input.length();
        }

        public char get(int offset) {
            return input.charAt(index + offset);
        }

        public void advance() {
            index++;
            length++;
        }

        public void skip() {
            length = 0;
        }

        public Token emit(Token.Type type) {
            int start = index - length;
            skip();
            return new Token(type, input.substring(start, index), start);
        }

    }

}
