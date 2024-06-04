package task3;

public class Product {

    private int id;
    private String name;
    private String author;

    public Product() {
        this.id = 0;
        this.name = "Book";
        this.author = "Author";
    }

    public Product(int id, String name, String author) {
        this.id = id;
        this.name = name;
        this.author = author;

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    @Override
    public String toString() {
        return "Product - " +
                "ID = " + id +
                ", Name = " + name +
                ", Author = " + author;

    }
}