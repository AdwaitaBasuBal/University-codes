public class Lab7_1 {
    // Write a program in Java to find the average
    // of all user entered numbers at the command line
    public static void main(String args[]) {

        int sum = 0;

        for (int i = 0; i < args.length; i++) {
            sum += Integer.parseInt(args[i]);
        }
        int average = sum / args.length;

        System.out.println("Average : " + average);
    }
}