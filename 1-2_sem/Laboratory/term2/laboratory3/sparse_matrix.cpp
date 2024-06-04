#include "sparse_matrix.hpp"
#include <fstream>
using std::ostream;
// Matrix::Matrix()
// {
//     Width = 0;
//     Height = 0;
//     string = nullptr;
// }
Matrix::Matrix(const int &i, const int &j)
{
    Height = i;
    Width = j;
    string = new List[Height];
}
Matrix::Matrix(const Matrix &m)
{
    Height = m.Height;
    Width = m.Width;
    string = new List[Height];
    for (int i = 0; i < Height; i++)
        for (int j = 0; j < Width; j++)
            string[i].push_back(m.string[i][j], j);
}
Matrix::~Matrix()
{
    for (int i = 0; i < Height; i++)
    {
        string[i].~List();
    }
}
// Matrix operator+(const Matrix &m1, const Matrix &m2)
// {
// }
// Matrix operator*(const Matrix &m1, const Matrix &m2)
// {
// }
int Matrix::get_heigth() const
{
    return Height;
}
int Matrix::get_width() const
{
    return Width;
}
void Matrix::read(const char *ch)
{
    using std::cout;
    using std::ifstream;
    ifstream in;
    int dat;
    in.open(ch);
    if (in.is_open())
    {

        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                in >> dat;
                if (dat)
                    string[i].push_back(dat, j);
                //cout << dat << ' ';
            }
        }
        //cout << '\n';
    }
    else
        cout << "File is missing!" << '\n';
    in.close();
}
void Matrix::save(const char *ch)
{
    using std::ofstream;
    ofstream out(ch);
    if (out.is_open())
    {
        for (int i = 0; i < Height; i++)
        {
            string[i].print(Width, out);
            out << '\n';
        }
    }
    else
        std::cout << "File is missing!" << '\n';
    out.close();
}
std::ostream &operator<<(std::ostream &out, const Matrix &m)
{
    for (int i = 0; i < m.Height; i++)
    {
        m.string[i].print(m.Width, out);
        out << '\n';
    }
    return out;
}
List::List()
{
    // std::cout << "\ncalling constructor\n";
    head = tail = nullptr;
}
List::~List()
{
    // std::cout << "calling destructor\n";
    erase();
}
void List::push_back(const int &data, const int &j)
{
    Node *pv = new Node;
    pv->data = data;
    pv->j = j;
    pv->next = nullptr;
    size++;
    if (!head)
    {
        head = pv;
        pv->prev = nullptr;
        tail = head;
    }
    else
    {
        tail->next = pv;
        pv->prev = tail;
        tail = pv;
    }
}
int List::find(const int &j)
{
    Node *pv = head;
    while (pv)
    {
        if (pv->j == j)
            return pv->data;
        pv = pv->next;
    }
    return 0;
}
void List::print(const int &width, ostream &out)
{
    Node *pv = this->head;
    for (int i = 0; i < width; i++)
    {
        if (!pv || pv->j != i)
        {
            out << 0 << '\t';
            continue;
        }
        if (pv->j == i)
            out << pv->data << '\t';
        pv = pv->next;
    }
}
void List::erase()
{
    Node *pv;
    while (head)
    {
        pv = head;
        head = head->next;
        delete pv;
    }
}
int List::operator[](const int &k)
{
    Node *pv = head;
    for (int i = 0; i < get_size(); i++)
    {
        if (pv->j == k)
            return pv->data;
        pv = pv->next;
    }
    return 0;
}
Matrix operator+(const Matrix &m1, const Matrix &m2)
{
    // if (m1.get_width() == m2.get_width() && m1.get_heigth() == m2.get_heigth())
    // {
    Matrix result(m1.get_heigth(), m1.get_width());
    for (int i = 0; i < m1.get_heigth(); i++)
    {
        for (int j = 0; j < m1.get_width(); j++)
            result.string[i].push_back(m1.string[i][j] + m2.string[i][j], j);
    }
    return result;
    // }
    // else
    //     std::cerr << "Different matrix";
}
List *Matrix::operator[](const int &i)
{
    return (string + i);
}
Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    Matrix m(m1.get_heigth(), m1.get_width());
    int x = 0;
    for (int i = 0; i < m1.get_heigth(); i++)
    {
        for (int j = 0; j < m1.get_width(); j++)
        {
            x = 0;
            // for (int i1 = 0; i1 < m1.get_heigth(); i1++)
            for (int k = 0; k < m1.get_width(); k++)
            {
                x += m1.string[i][k] * m2.string[k][j];
                // std::cout << m1.string[i][k] << '*' << m2.string[k][j] << ' ';
            }
            // std::cout << " pushing back " << x << '\n';
            m.string[i].push_back(x, j);
        }
    }
    return m;
}
