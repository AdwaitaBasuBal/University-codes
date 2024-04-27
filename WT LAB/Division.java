import java.util.*;

public class Division {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        float a, b;
        float c;
        int d;
        do {
            System.out.println("Enter the 1st number:");
            a = scan.nextInt();
            System.out.println("Enter the 2nd number:");
            b = scan.nextInt();
            try {
                c = a / b;
                System.out.println("The result of division: " + c);
            }

            catch (ArithmeticException e) {
                System.out.println("Exception detected. ");
            }

            finally {
                System.out.println(" Enter 1 to try again, 0 to exit.");
                d = scan.nextInt();
            }
        } while (d == 1);
    }
}