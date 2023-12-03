
//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions : 

// Constructors: 
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)

class Box {
public:
    int l, b, h;
    
    Box(): l(0), b(0), h(0) {}
    Box(int l, int b, int h): l(l), b(b), h(h) {}
    Box(const Box& other): l(other.l), b(other.b), h(other.h) {}
    
    int getLength() { return l; }
    int getBreadth() { return b; }
    int getHeight() { return h; }
    long long CalculateVolume() { return l * b * h; }
    
    bool operator<(const Box& other) {
        return l < other.l
            || (b < other.b && l == other.l)
            || (h < other.h && l == other.l && b == other.b);
    }
};

std::ostream& operator<<(std::ostream& os, const Box& b) {
    return os << b.l <<' ' << b.b << ' ' << b.h ;
}
