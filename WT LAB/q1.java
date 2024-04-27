import java.util.*;

public class q1 {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("String: ");
        String input = sc.nextLine();
        input = input.trim();
        StringBuilder inputBuild = new StringBuilder();
        inputBuild.append(input);
        inputBuild.reverse();
        if (input.equalsIgnoreCase(inputBuild.toString())) {
            System.out.println("It is in Palindrome");
        } else {
            System.out.println("Not in Palindrome");
        }
        sc.close();
    }
}