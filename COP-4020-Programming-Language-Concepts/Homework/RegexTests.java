package plc.homework;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.regex.Pattern;
import java.util.stream.Stream;

/**
 * Contains JUnit tests for {@link Regex}. Test structure for steps 1 & 2 are
 * provided, you must create this yourself for step 3.
 *
 * To run tests, either click the run icon on the left margin, which can be used
 * to run all tests or only a specific test. You should make sure your tests are
 * run through IntelliJ (File > Settings > Build, Execution, Deployment > Build
 * Tools > Gradle > Run tests using <em>IntelliJ IDEA</em>). This ensures the
 * name and inputs for the tests are displayed correctly in the run window.
 */
public class RegexTests {

    /**
     * This is a parameterized test for the {@link Regex#EMAIL} regex. The
     * {@link ParameterizedTest} annotation defines this method as a
     * parameterized test, and {@link MethodSource} tells JUnit to look for the
     * static method {@link #testEmailRegex()}.
     *
     * For personal preference, I include a test name as the first parameter
     * which describes what that test should be testing - this is visible in
     * IntelliJ when running the tests (see above note if not working).
     */
    @ParameterizedTest
    @MethodSource
    public void testEmailRegex(String test, String input, boolean success) {
        System.out.println("Here is " + Regex.EMAIL);
        test(input, Regex.EMAIL, success);
    }

    /**
     * This is the factory method providing test cases for the parameterized
     * test above - note that it is static, takes no arguments, and has the same
     * name as the test. The {@link Arguments} object contains the arguments for
     * each test to be passed to the function above.
     */
    public static Stream<Arguments> testEmailRegex() {
        return Stream.of(
                Arguments.of("Alphanumeric", "thelegend27@gmail.com", true),
                Arguments.of("UF Domain", "otherdomain@ufl.edu", true),
                Arguments.of("Dot in User", "user.name@domain.com", true),
                Arguments.of("Dashes", "user-name.mail@some-domain.ca", true),
                Arguments.of("UF Domain", "user_with_underscore@hogwarts.gb", true),
                Arguments.of("Missing Domain Dot", "missingdot@gmailcom", false),
                Arguments.of("Symbols", "symbols#$%@gmail.com", false),
                Arguments.of("Subdomains", "username@subdomain.domain.com", false),
                Arguments.of("Country", "username@domain.com.au", false),
                Arguments.of("No @ Symbol", "noatsymbolAtgmail.com", false)
        );
    }

    @ParameterizedTest
    @MethodSource
    public void testEvenStringsRegex(String test, String input, boolean success) {
        test(input, Regex.EVEN_STRINGS, success);
    }

    public static Stream<Arguments> testEvenStringsRegex() {
        return Stream.of(
                //what has ten letters and starts with gas?
                Arguments.of("10 Characters", "automobile", true),
                Arguments.of("14 Characters", "i<3pancakes10!", true),
                Arguments.of("Special Characters", "!@#$%^&*(),./;", true),
                Arguments.of("Max Characters", "exactlytwentyyeehaw!", true),
                Arguments.of("Spaces", "Spaces Included!", true),
                Arguments.of("6 Characters", "6chars", false),
                Arguments.of("13 Characters", "i<3pancakes9!", false),
                Arguments.of("Over Max", "morethantwentycharacters", false),
                Arguments.of("21 Characters", "isitanoffbyoneerror??", false),
                Arguments.of("9 Characters", "offbyone?", false)
        );
    }

    @ParameterizedTest
    @MethodSource
    public void testIntegerListRegex(String test, String input, boolean success) {
        test(input, Regex.INTEGER_LIST, success);
    }

    public static Stream<Arguments> testIntegerListRegex() {
        return Stream.of(
                Arguments.of("Single Element", "[1]", true),
                Arguments.of("Multiple Elements", "[1,2,3]", true),
                Arguments.of("Elements with Spaces", "[1, 2, 3]", true),
                Arguments.of("Inconsistent Spaces", "[1,2,   3]", true),
                Arguments.of("Empty List", "[]", true),
                Arguments.of("Missing Brackets", "1,2,3", false),
                Arguments.of("Missing Commas", "[1 2 3]", false),
                Arguments.of("Empty String", "", false),
                Arguments.of("Spaces Before Commas", "[1 ,2 ,3]", false),
                Arguments.of("Negative Integer", "[-1]", false)
        );
    }

    @ParameterizedTest
    @MethodSource
    public void testNumberRegex(String test, String input, boolean success) {
        test(input, Regex.NUMBER, success);
    }

    public static Stream<Arguments> testNumberRegex() {
        return Stream.of(
                Arguments.of("Single Number", "1", true),
                Arguments.of("Signed Number", "-1.0", true),
                Arguments.of("Multiple Digits", "123.456", true),
                Arguments.of("Leading Zeros", "007", true),
                Arguments.of("Trailing Zeros", "123.000", true),
                Arguments.of("Trailing Decimal", "1.", false),
                Arguments.of("Leading Decimal", ".5", false),
                Arguments.of("Multiple Decimals", "1.5.6.8", false),
                Arguments.of("Multiple Signs", "-+1.", false),
                Arguments.of("Non-Digit", "one", false)
        );
    }

    @ParameterizedTest
    @MethodSource
    public void testStringRegex(String test, String input, boolean success) {
        test(input, Regex.STRING, success);
    }

    public static Stream<Arguments> testStringRegex() {
        return Stream.of(
                Arguments.of("Double Quotes", "\"\"", true),
                Arguments.of("Words and Special Characters", "\"Hello, World!\"", true),
                Arguments.of("Escaped Character", "\"1\\t2\"", true),
                Arguments.of("Multiple Escapes", "\"First\\tSecond\\n\"", true),
                Arguments.of("Quote", "\"\\'There will always be rocks in the road ahead of us.\\n" +
                        "They will be stumbling blocks or stepping stones;\\n" +
                        "it all depends on how you use them.\\n\\'" +
                        "-Friedrich Nietzsche\"", true),
                Arguments.of("Unterminated String", "\"unterminated", false),
                Arguments.of("Invalid Escape", "\"invalid\\escape\"", false),
                Arguments.of("Uninitialized String", "uninitialized\"", false),
                Arguments.of("Empty String", "", false),
                Arguments.of("Unterminated String", "Multiple\n Lines", false)
        );
    }

    /**
     * Asserts that the input matches the given pattern. This method doesn't do
     * much now, but you will see this concept in future assignments.
     */
    private static void test(String input, Pattern pattern, boolean success) {
        Assertions.assertEquals(success, pattern.matcher(input).matches());
    }

}
