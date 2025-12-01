public class Nota {
    private Student student;
    private Tema tema;
    private double value;
    private String profesor;

    public Nota(Student student, Tema tema, double value, String profesor) {
        this.student = student;
        this.tema = tema;
        this.value = value;
        this.profesor = profesor;
    }

    public Student getStudent() {
        return student;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public Tema getTema() {
        return tema;
    }

    public void setTema(Tema tema) {
        this.tema = tema;
    }

    public double getValue() {
        return value;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public String getProfesor() {
        return profesor;
    }

    public void setProfesor(String profesor) {
        this.profesor = profesor;
    }
}
