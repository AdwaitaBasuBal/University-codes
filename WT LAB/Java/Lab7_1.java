import java.util.*;

public class Lab7_1 {
    public static void main(String[] args) {
        try (Scanner obj = new Scanner(System.in)) {
            System.out.println("Enter no of numbers");
            int n;
            n = obj.nextInt();
            int sum = 0;
            int x;
            System.out.println("enter the nos");
            for (int i = 0; i < n; i++) {
                x = obj.nextInt();
                sum += x;
            }
            int avg;
            avg = sum / n;
            System.out.println("average is " + avg);
        }
    }
}