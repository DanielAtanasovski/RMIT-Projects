package types;

public class Student {

	private String studentNumber;
	private String studentName;
	private String degreeName;
	private String DOB;
	private float CGPA;
	private int graduationYear;

	public Student(String studentNumber, String studentName, String degreeName, String DOB, float CGPA,
			int graduationYear) {
		this.studentNumber = studentNumber;
		this.studentName = studentName;
		this.degreeName = degreeName;
		this.DOB = DOB;
		this.CGPA = CGPA;
		this.graduationYear = graduationYear;
	}

	public String getStudentNumber() {
		return studentNumber;
	}

	public int getGraduationYear() {
		return graduationYear;
	}

	public float getCGPA() {
		return CGPA;
	}

	public String getDOB() {
		return DOB;
	}

	public String getDegreeName() {
		return degreeName;
	}

	public String getStudentName() {
		return studentName;
	}

	@Override
	public String toString() {
		return String.format("%s-%s-%s-%s-%f-%d", studentNumber, studentName, degreeName, DOB, CGPA, graduationYear);
	}

}
