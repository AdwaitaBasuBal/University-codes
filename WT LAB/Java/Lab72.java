import java.util.*;

public class Lab72 {

    public static void main(String[] args) {

        System.out.println("enter rows and columns of matrices");
        int r, c;
        try (Scanner sc = new Scanner(System.in)) {
            r = sc.nextInt();
            c = sc.nextInt();

            int[][] arr = new int[r][c];
            int[][] arr1 = new int[r][c];

            System.out.println("enter the nos of 1st matrix");

            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    arr[i][j] = sc.nextInt();

                }
            }
            System.out.println("enter the nos of 2st matrix");

            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    arr1[i][j] = sc.nextInt();

                }
            }

            int[][] sum = new int[r][c];
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    sum[i][j] = arr[i][j] + arr1[i][j];
                }
            }

            System.out.println("Sum matrix");

            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    System.out.print(sum[i][j] + " ");
                }
                System.out.println();
            }
        }

    }

}
