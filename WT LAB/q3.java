import java.util.*;

public class q3 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Enter String 1:");
        String str1 = scan.nextLine();
        System.out.println("Enter String 2:");
        String str2 = scan.nextLine();

        if (str1.contains(str2)) {
            System.out.println("String 1 contrains String 2");
        } else if (str2.contains(str1)) {
            System.out.println("String 2 contrains String 1");
        } else {
            System.out.println("Neither string contain the other.");
        }
    }
}