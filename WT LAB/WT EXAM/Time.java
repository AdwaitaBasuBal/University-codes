import java.util.Scanner;

public class Time {
    Scanner scan = new Scanner(System.in);
    int Hours[] = new int[2];
    int Minutes[] = new int[2];

    Time() {
        System.out.println("Enter time 1: ");
        Hours[0] = scan.nextInt();
        Minutes[0] = scan.nextInt();
        System.out.println("Enter time 2: ");
        Hours[1] = scan.nextInt();
        Minutes[1] = scan.nextInt();
    }

    void Add_nos() {
        int x = Hours[0] + Hours[1];
        int y = Minutes[0] + Minutes[1];
        int z = y / 60;
        x = x + z;
        y = y - (z * 60);
        System.out.println("The sum of times: " + x + " Hours " + y + " Mins. ");
    }

    void Sub_nos() {
        int x = Math.abs(Hours[0] - Hours[1]);
        int y = Minutes[0] - Minutes[1];
        int z = y / 60;
        x = x + z;
        y = y - (z * 60);
        System.out.println("The difference of times: " + x + " Hours " + y + " Mins. ");
    }

    public static void main(String[] args) {
        Time t = new Time();
        t.Add_nos();
        t.Sub_nos();
    }
}
