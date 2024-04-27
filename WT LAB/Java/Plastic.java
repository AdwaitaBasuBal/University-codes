import java.util.Scanner;

public class Plastic {
  Scanner scan = new Scanner(System.in);
  int l, b;

  public void Two_Cost() {
    System.out.println("Enter the dimensions(2) in feet:");
    l = scan.nextInt();
    b = scan.nextInt();

    int cost_2D = l * b * 40;

    System.out.println("The cost for the sheet is: Rs" + cost_2D);
  }
}

class boxx extends Plastic {
  int h;

  public void Three_Cost() {
    System.out.println("Enter the dimensions(3) in feet:");
    l = scan.nextInt();
    b = scan.nextInt();
    h = scan.nextInt();

    int cost_3D = l * b * h * 60;

    System.out.println("The cost for the box is: Rs" + cost_3D);
  }

  public static void main(String[] args) {
    Plastic b1 = new Plastic();
    b1.Two_Cost();

    boxx b2 = new boxx();
    b2.Three_Cost();

  }
}