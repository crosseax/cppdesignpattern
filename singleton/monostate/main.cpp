// better not use it

class Printer {
    static int id;
public:
    int get_id() const { return id; }
    void set_id(int value) { id = value; }
};

int main()
{
    Printer p;
    int id = p.get_id();

    Printer p2;
    int id2 = p2.get_id();

    // you think you working with it, while you're not
    // both instances is working with the same storage

    return 0;
}