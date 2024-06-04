package task2;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;

public class ClientSocketTask9 {
    private Socket sock = null;
    private ObjectOutputStream out = null;
    private ObjectInputStream in = null;

    public ClientSocketTask9(String ip, int port) throws IOException {
        sock = new Socket(ip, port);
        out = new ObjectOutputStream(sock.getOutputStream());
        in = new ObjectInputStream(sock.getInputStream());
    }

    public void addId(int id, int ID) throws IOException {
        out.writeObject("addID");
        out.writeObject(id);
        out.writeObject(ID);
    }

    public void deleteID(int id) throws IOException {
        out.writeObject("deleteID");
        out.writeObject(id);
    }

    public void addName(int id, String name) throws IOException {
        out.writeObject("addName");
        out.writeObject(id);
        out.writeObject(name);
    }

    public void deleteName(int id) throws IOException {
        out.writeObject("deleteName");
        out.writeObject(id);
    }

    public void addManufacturer(int id, String manufacturer) throws IOException {
        out.writeObject("addAuthor");
        out.writeObject(id);
        out.writeObject(manufacturer);
    }

    public void deleteManufacturer(int id) throws IOException {
        out.writeObject("deleteAuthor");
        out.writeObject(id);
    }

    public ArrayList<Product> getProductById(int id) throws IOException, ClassNotFoundException {
        out.writeObject("getNewsById");
        out.writeObject(id);
        return (ArrayList<Product>) in.readObject();
    }

    public ArrayList<Product> getProducts() throws IOException, ClassNotFoundException {
        out.write("getProducts");
        return (ArrayList<Product>) in.readObject();
    }

    public void disconnect() throws IOException {
        sock.close();
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        ClientSocketTask9 client = new ClientSocketTask9("localhost", 12345);
        ArrayList<Product> products = client.getProducts();
        for (Product product : products) {
            System.out.println(product.getId() + "  " + product.getName() + " " + product.getAuthor());
        }
        client.disconnect();
    }
}
