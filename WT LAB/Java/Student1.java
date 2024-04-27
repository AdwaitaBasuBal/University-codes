import java.util.*;

//Write a student class in Java with data members as rollno, 
//course and a method as register for enrolling to a course. 
//Write another class KIITIAN derived from student having a method 
//hostel request to request for hostel accomodation. Write the complete
//program to check the inheritance of KIITIAN object.

public class Student1 {
    Scanner scan = new Scanner(System.in);
    int roll_no;
    String course;
    String accomodation;

    public void course_allot() {
        System.out.println("Enter the course you want to enroll in:");
        course = scan.nextLine();
    }

}

class KIITian extends Student1 {
    void hostel_accomodation() {
        System.out.println("Enter the hostel you want to be accomodated in:");
        accomodation = scan.nextLine();
    }

    public static void main(String[] args) {
        KIITian s1 = new KIITian();
        s1.roll_no = 21053229;
        s1.course_allot();
        s1.hostel_accomodation();

        System.out.println("Roll number: " + s1.roll_no);
        System.out.println("Course: " + s1.course);
        System.out.println("Hostel Accomodation: " + s1.accomodation);

    }
}