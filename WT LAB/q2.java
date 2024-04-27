import java.util.*;

public class q2 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Enter String 1:");
        String str1 = scan.nextLine();

        System.out.println("Enter String 2:");
        String str2 = scan.nextLine();

        String str3 = str1.concat(str2);
        System.out.println("\n\nAppended string is: " + str3);

        int a;
        System.out.println("\nEnter String number to perform replace operation:");
        a = scan.nextInt();
        System.out.println("\nEnter the substring you want to be replaced:");
        String substr1 = scan.nextLine();
        substr1 = scan.nextLine();
        System.out.println("\nEnter the substring you want to replace with:");
        String substr2 = scan.nextLine();

        if (a == 1) {
            String str4 = str1.replace(substr1, substr2);
            System.out.println("\n\nThe updated string is: " + str4);
        } else {
            String str4 = str2.replace(substr1, substr2);
            System.out.println("\n\nThe updated stirng is: " + str4);
        }

        System.out.println("\nEnter String number to change a character of:");
        a = scan.nextInt();
        System.out.println("\nEnter the char you want to be replaced:");
        String c1 = scan.nextLine();
        c1 = scan.nextLine();
        System.out.println("\nEnter the char you want to replace with:");
        String c2 = scan.nextLine();

        if (a == 1) {
            String str5 = str1.replace(c1, c2);
            System.out.println("\n\nThe updated string is: " + str5);
        } else {
            String str5 = str2.replace(c1, c2);
            System.out.println("\n\nThe updated string is: " + str5);
        }

        System.out.println("\nEnter String in which you want to insert the other string:");
        a = scan.nextInt();
        System.out.println("\nEnter the position in which you want to insert the string:");
        int b = scan.nextInt();

        if (a == 1) {
            String str6 = str1.substring(0, b) + str2 + str1.substring(b);
            System.out.println("\n\nThe resultant string is: " + str6);
        } else {
            String str6 = str2.substring(0, b) + str1 + str2.substring(b);
            System.out.println("\n\nThe resultant string is: " + str6);
        }
    }
}