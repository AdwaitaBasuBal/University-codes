import java.util.Scanner;

public class Triangle {
    Scanner scan = new Scanner(System.in);
    int a, b, c;

    Triangle() {
        System.out.println("Enter side 1:");
        a = scan.nextInt();
        System.out.println("Enter side 2:");
        b = scan.nextInt();
        System.out.println("Enter side 3:");
        c = scan.nextInt();
        try {
            if (a + b <= c || b + c <= a || a + c <= b) {
                throw new ExceptionTriangle("Invalid triangle, Following outputs are wrong");
            }
        } catch (ExceptionTriangle e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    void Area() {
        int s = (a + b + c) / 2;
        double area = Math.sqrt(s * (s - a) * (s - b) * (s - c));
        System.out.println("\nThe area:" + area);
    }

    void Perimeter() {
        int per = a + b + c;
        System.out.println("\nThe perimeter " + per);
    }

    public static void main(String[] args) {
        Triangle t = new Triangle();
        t.Area();
        t.Perimeter();
    }

    class ExceptionTriangle extends Exception {
        public ExceptionTriangle(String errorMessage) {
            super(errorMessage);
        }
    }
}
