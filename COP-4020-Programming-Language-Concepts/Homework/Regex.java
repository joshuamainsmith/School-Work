package plc.homework;

import java.util.regex.Pattern;

/**
 * Contains {@link Pattern} constants, which are compiled regular expressions.
 * See the assignment page for resources on regexes as needed.
 */
public class Regex {

    public static final Pattern
            EMAIL = Pattern.compile("[A-Za-z0-9._\\-]+@[A-Za-z0-9-]*\\.[a-z]{2,3}"),
            EVEN_STRINGS = Pattern.compile("(..){5,10}"), // Source: https://stackoverflow.com/questions/3384207/match-string-of-odd-length
            INTEGER_LIST = Pattern.compile("[\\[]((\\d+)(,\\s*\\d+)*)?[\\]]"), // Source: https://stackoverflow.com/questions/1396084/regex-for-comma-delimited-list
            NUMBER = Pattern.compile("(\\-|\\+)?\\d+(\\.\\d+)?"), // Source: https://regexper.com/#%28%5C-%7C%5C%2B%29%3F%5Cd%2B%28%5C.%5Cd%2B%29%3F
            STRING = Pattern.compile("[\"]([^\\\\]*?(\\\\(b|r|n|t|\\'|\\\"|\\\\))?)+[\"]"); // Source: https://stackoverflow.com/questions/9770860/using-regex-to-match-any-character-except

}