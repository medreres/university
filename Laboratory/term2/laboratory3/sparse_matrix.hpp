#ifndef SPARSE_MATRIX
#define SPARSE_MATRIX
#include <iostream>
struct Node
{
    int data;
    int j;
    Node *next;
    Node *prev;
};
class List
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    List();
    ~List();
    void push_back(const int &data, const int &j);
    int find(const int &j);
    void print(const int &width, std::ostream &out);
    int operator[](const int &k);
    void erase();
    int get_size() const { return size; }
};
class Matrix
{
private:
    int Width;
    int Height;
    List *string;

public:
    //constructor and destructor
    Matrix(const Matrix &m);
    Matrix(const int &i, const int &j);
    ~Matrix();

    //operators
    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    List *operator[](const int &i);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);

    //essential functions
    int get_width() const;
    int get_heigth() const;

    //read from file
    void read(const char *ch);
    void save(const char *ch);
};
#endif
