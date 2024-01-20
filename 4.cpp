#include <iostream>

using namespace std;

//Abstract Class Shape
class Shape
{
public:
    virtual void print() = 0;
    virtual int type() = 0;
    static bool is_equal(Shape *, Shape *);
    Shape *clone();
};
//Class Circle
class Circle : public Shape
{
protected:
    float r;

public:
    float x, y;

    Circle(float x, float y, float r)
    {
        this->x = x;
        this->y = y;
        Set_R(r);
    }

    void Set_R(float r)
    {
        while (1)
        {
            if (r < 0)
            {
                cout << "invalid for r\n";
                cin >> r;
            }
            else
            {
                this->r = r;
                break;
            }
        }
    }
    float Get_R() const { return r; };
    int type() { return 1; };
    void print()
    {
        cout << "Center=(" << x << "," << y << ")";
        cout << "r=" << r;
    }
    static bool is_equal(Circle c1, Circle c2)
    {
        return c1.r == c2.r && c1.x == c2.x && c1.y == c2.y;
    }
};
//Class Rectangle
class Rectangle : public Shape
{
protected:
    float w, h;

public:
    Rectangle(float w = 0, float h = 0)
    {
        Set_h(h);
        Set_w(w);
    }
    void Set_w(float w)
    {
        while (1)
        {
            if (w < 0)
            {
                cout << "invalid for w\n";
                cin >> w;
            }
            else
            {
                this->w = w;
                break;
            }
        }
    }
    void Set_h(float h)
    {
        while (1)
        {
            if (h < 0)
            {
                cout << "invalid for h\n";
                cin >> h;
            }
            else
            {
                this->h = h;
                break;
            }
        }
    }
    float Get_w() const { return w; };
    float Get_h() const { return h; };
    int type() { return 2; };
    void print()
    {
        cout << " Rectangle:"
             << "w=" << w << "h=" << h;
    }
    static bool is_equal(Rectangle r1, Rectangle r2)
    {
        return r1.w == r2.w && r1.h == r2.h;
    }
};
//Shape Is_Equal
bool Shape::is_equal(Shape *p, Shape *q)
{
    if (1 == p->type() && p->type() == q->type()) // Circle
    {
        return Circle::is_equal(*(Circle *)(p), *(Circle *)(q));
    }
    else if (2 == p->type() && p->type() == q->type()) // Rectangle
    {
        return Rectangle::is_equal(*(Rectangle *)(p), *(Rectangle *)(q));
    }
    return false;
}
//Shape Clone
Shape *Shape::clone()
{
    if (type() == 1)
    {
        Circle c = *(Circle *)this;
        Circle *ptr = new Circle(c.x, c.y, c.Get_R());
        return ptr;
    }
    if (type() == 2)
    {
        Rectangle r = *(Rectangle *)this;
        Rectangle *ptr = new Rectangle(r.Get_w(), r.Get_h());
        return ptr;
    }
}

struct Node
{
    Shape *ptr;
    Node *next;
};
////////////// Start MySet ///////////////
class MySet
{
private:
    Node *head;

public:
    MySet()
    {
        head = nullptr;
    }
    void insert(Shape *ptr);
    bool search(Shape *ptr);
    void printAll();
    void Remove(Shape *ptr);
    int numberRect();
    int numberCir();
    void RemoveRectangle();
    void printcircle();
    void printRectangle();
    void ClearAll();
    static MySet Union(MySet, MySet);
    static MySet Intersection(MySet, MySet);
    static MySet Difference(MySet, MySet);
};

// Intersection
MySet MySet::Intersection(MySet first, MySet second)
{
    MySet result;
    Node *curr = first.head;
    while (curr)
    {
        if (second.search(curr->ptr))
            result.insert(curr->ptr->clone());
        curr = curr->next;
    }
    return result;
}
// Difference
MySet MySet::Difference(MySet first, MySet second)
{
    MySet result;
    Node *curr = first.head;
    while (curr)
    {
        if (!second.search(curr->ptr))
            result.insert(curr->ptr->clone());
        curr = curr->next;
    }
    return result;
}
// union
MySet MySet::Union(MySet first, MySet second)
{
    MySet result;
    Node *current = first.head;
    while (current != nullptr)
    {
        result.insert(current->ptr->clone());
        current = current->next;
    }

    current = second.head;
    while (current != nullptr)
    {
        result.insert(current->ptr->clone());
        current = current->next;
    }
    return result;
}
//Print Circle
void MySet::printcircle()
{
    Node *curr = head;
    if (!curr)
    {
        cout << "No Member..";
        return;
    }

    while (curr)
    {
        if (curr->ptr->type() == 1)
        {
            curr->ptr->print();
            cout << endl;
        }
        curr = curr->next;
    }
}
//Print Rectangle
void MySet::printRectangle()
{
    Node *curr = head;
    if (!curr)
    {
        cout << "No Member..";
        return;
    }
    while (curr)
    {
        if (curr->ptr->type() == 2)
        {
            curr->ptr->print();
            cout << endl;
        }
        curr = curr->next;
    }
}
//ClearAll
void MySet::ClearAll()
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp->ptr;
        delete temp;
    }
}
//RemoveRectangles
void MySet::RemoveRectangle()
{
    Node *curr = head;
    Node *pre = nullptr;
    if (!curr)
    {
        cout << "No Member..";
        return;
    }
    while (curr)
    {
        if (curr->ptr->type() == 2)
        {
            Node *temp = curr;
            curr = curr->next;
            if (pre == nullptr)
            {
                head = curr;
            }
            else
            {
                pre->next = curr; 
            }
            delete temp->ptr;
            delete temp;
        }
        else
        {
            pre = curr;
            curr = curr->next;
        }
    }
}
// Number Rectangle
int MySet::numberRect() 
{
    Node *current = head;
    int count = 0;

    while (current != nullptr)
    {
        if (current->ptr->type() == 2)
        {
            count++;
        }
        current = current->next;
    }
    return count;
}
// Number Circle
int MySet::numberCir() 
{
    Node *current = head;
    int count = 0;

    while (current != nullptr)
    {
        if (current->ptr->type() == 1)
        {
            count++;
        }

        current = current->next;
    }
    return count;
}
// Remove Shape
void MySet::Remove(Shape *K)
{
    Node *curr = head;
    Node *pre = nullptr;
    if (!curr)
    {
        cout << "No Member..";
        return;
    }
    while (curr)
    {
        if (Shape::is_equal(curr->ptr, K))
        {
            if (pre == nullptr)
            {
                head = curr->next;
            }
            else
            {
                pre->next = curr->next;
            }
            delete curr->ptr;
            delete curr;
            cout << "Removed\n";
            break;
        }

        pre = curr;
        curr = curr->next;
    }
    if (curr == nullptr)
        cout << "Shape not found in the list." << endl;
}
//PrintAll
void MySet::printAll()
{
    Node *current = head;
    if (current == NULL)
    {
        cout << "There are no members..\n";
        return;
    }
    cout << "{";
    while (current)
    {
        current->ptr->print();
        if (current->next != NULL)
            cout << ",";
        current = current->next;
    }
    cout << "}";
}
//Search
bool MySet::search(Shape *key)
{
    Node *curr = head;
    while (curr)
    {
        if (Shape::is_equal(curr->ptr, key))
            return true;
        curr = curr->next;
    }
    return false;
}
// Add Shape
void MySet::insert(Shape *ptr)
{
    if (search(ptr))
        return;

    Node *temp = new Node;
    temp->ptr = ptr;
    temp->next = nullptr;

    if (!head)
    {
        head = temp;
        return;
    }

    Node *curr = head;
    while (curr->next)
    {
        curr = curr->next;
    }

    curr->next = temp;
}

int main()
{

    MySet first, secound;
    MySet result3, Union1, Intersection1;
    int Choise;
    do
    {
        cout << "\n\" Menu \"";
        cout << "\n1.Add The Shape to The Set1:\n";
        cout << "2.Add The Shape to The Set2:\n";
        cout << "3.Print the Shapes of The Set1:\n";
        cout << "4.Print the Shapes of The Set2:\n";
        cout << "5.Search in the Set1:\n";
        cout << "6.Search in the Set2:\n";
        cout << "7.Number Of Member Set1:\n";
        cout << "8.Number Of Member Set2:\n";
        cout << "9.Print Circles in Set1:\n";
        cout << "10.Print Circles in Set2:\n";
        cout << "11.Remove The Shape to The Set1:\n";
        cout << "12.Remove The Shape to The Set2:\n";
        cout << "13.Remove Rectangles in the set1:\n";
        cout << "14.Remove Rectangles in the set2:\n";
        cout << "15.ClearAll in the Set1:\n";
        cout << "16.ClearAll in the Set2:\n";
        cout << "17.The union of two sets:\n";
        cout << "18.Subscription of two sets:\n";
        cout << "19.Difference of two sets:\n";
        cout << "20.Exit:\n";
        cin >> Choise;

        switch (Choise)
        {
        case 1:
        {
            int r;
            cout << "1.Rectangle\n";
            cout << "2.Circle\n";
            cin >> r;
            if (1 == r)
            {
                int W, H;
                cout << "Enter W,H:\n";
                cin >> W >> H;
                Rectangle *h = new Rectangle(W, H);
                first.insert(h);
                cout << "Added:)\n";
            }
            else
            {
                int x, y, r;
                cout << "Enter x,y,r\n";
                cin >> x >> y >> r;
                Circle *p = new Circle(x, y, r);
                first.insert(p);
                cout << "Added:)\n\n";
            }
        }
        break;
        case 2:
        {
            int b;
            cout << "1.Rectangle\n";
            cout << "2.Circle\n";
            cin >> b;
            if (1 == b)
            {
                int W, H;
                cout << "Enter W,H:\n";
                cin >> W >> H;
                Rectangle *h = new Rectangle(W, H);
                secound.insert(h);
                cout << "Added:)\n";
            }
            else
            {
                int x, y, r;
                cout << "Enter x,y,r\n";
                cin >> x >> y >> r;
                Circle *p = new Circle(x, y, r);
                secound.insert(p);
                cout << "Added:)\n";
            }
        }
        break;
        case 3:
        {
            cout << "\nPrint Shapes in set1:\n";
            first.printAll();
        }
        break;
        case 4:
        {
            cout << "\nPrint Shapes in set2:\n";
            secound.printAll();
        }
        break;
        case 5:
        {
            int z;
            bool y2;
            cout << "1.Rectangle\n";
            cout << "2.Circle\n";
            cin >> z;
            if (1 == z)
            {
                int W, H;
                cout << "Enter W,H:\n";
                cin >> W >> H;
                Rectangle *h = new Rectangle(W, H);
                y2 = first.search(h);
            }
            else
            {
                int x, y, r;
                cout << "Enter x,y,r\n";
                cin >> x >> y >> r;
                Circle *p = new Circle(x, y, r);
                y2 = first.search(p);
            }
            if (y2 == true)
                cout << "Found it..\n";
            else
                cout << "Not Found..\n";
        }
        break;
        case 6:
        {
            int b1;
            bool y1;
            cout << "1.Rectangle\n";
            cout << "2.Circle\n";
            cin >> b1;
            if (1 == b1)
            {
                int W, H;
                cout << "Enter W,H:\n";
                cin >> W >> H;
                Rectangle *h = new Rectangle(W, H);
                y1 = secound.search(h);
            }
            else
            {
                int x, y, r;
                cout << "Enter x,y,r\n";
                cin >> x >> y >> r;
                Circle *p = new Circle(x, y, r);
                y1 = secound.search(p);
            }
            if (y1 == true)
                cout << "Found it..\n";
            else
                cout << "Not Found..\n";
        }
        break;
        case 7:
        {
            cout << "\nThe Number of members of the rectangle:" << first.numberRect() << endl;
            cout << "The Number of members of the Circle:" << first.numberCir() << endl;
            cout << "The Number of all members:" << (first.numberCir() + first.numberRect()) << endl;
        }
        break;
        case 8:
        {

            cout << "\nThe Number of members of the rectangle:" << secound.numberRect() << endl;
            cout << "The Number of members of the Circle:" << secound.numberCir() << endl;
            cout << "The Number of all members:" << (secound.numberCir() + secound.numberRect()) << endl;
        }
        break;
        case 9:
        {
            cout << "\n\nPrintCircles:\n";
            first.printcircle();
        }
        break;
        case 10:
        {
            cout << "\n\nPrintCircles:\n";
            secound.printcircle();
        }
        break;
        case 11:
        {
            int T;
            cout << "1.Rectangle\n";
            cout << "2.Circle\n";
            cin >> T;
            if (1 == T)
            {
                int W, H;
                cout << "Enter W,H:\n";
                cin >> W >> H;
                Rectangle *h = new Rectangle(W, H);
                first.Remove(h);
            }
            else
            {
                int x, y, r;
                cout << "Enter x,y,r\n";
                cin >> x >> y >> r;
                Circle *p = new Circle(x, y, r);
                first.Remove(p);
            }
        }
        break;
        case 12:
        {
            int T1;
            cout << "1.Rectangle\n";
            cout << "2.Circle\n";
            cin >> T1;
            if (1 == T1)
            {
                int W, H;
                cout << "Enter W,H:\n";
                cin >> W >> H;
                Rectangle *h = new Rectangle(W, H);
                secound.Remove(h);
            }
            else
            {
                int x, y, r;
                cout << "Enter x,y,r\n";
                cin >> x >> y >> r;
                Circle *p = new Circle(x, y, r);
                secound.Remove(p);
            }
        }
        break;
        case 13:
        {
            cout << "\nRemove Rectangles:\n";
            first.printRectangle();
            first.RemoveRectangle();
        }
        break;
        case 14:
        {
            cout << "\nRemove Rectangles:\n";
            secound.printRectangle();
            secound.RemoveRectangle();
        }
        break;
        case 15:
        {
            cout << "\nClearAll...\n";
            first.ClearAll();
        }
        break;
        case 16:
        {
            cout << "\nClearAll...\n";
            secound.ClearAll();
        }
        break;
        case 17:
        {
            cout << "\nThe union of two sets:\n";
            Union1 = Union1.Union(first, secound);
            Union1.printAll();
            Union1.ClearAll();
        }
        break;
        case 18:
        {
            cout << "\nSubscription of two sets:\n";
            Intersection1 = Intersection1.Intersection(first, secound);
            Intersection1.printAll();
            Intersection1.ClearAll();
        }
        break;
        case 19:
        {
            cout << "\nDifference of two sets:\n";
            result3 = result3.Difference(first, secound);
            result3.printAll();
            Intersection1.ClearAll();
        }
        break;
        case 20:
            cout << "Exit:(";
            exit(-1);
            break;
        default:
            cout << "Invalid Choice!";
            break;
        }

    } while (Choise != 0);
}
