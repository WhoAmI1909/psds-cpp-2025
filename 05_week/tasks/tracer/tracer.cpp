#include <string>


class Tracer {
    int id;             // unique identifier of the object
    std::string name;   // name of the object

public:
    static int counter;         // number of created objects
    static int default_ctor;    // number of calls to default constructor
    static int str_ctor;        // number of calls to constructor with string argument
    static int copy_ctor;       // number of calls to copy constructor
    static int move_ctor;       // number of calls to move constructor
    static int copy_assign;     // number of calls to copy assignment operator
    static int move_assign;     // number of calls to move assignment operator
    static int dtor;            // number of calls to destructor
    static int alive;           // number of currently alive objects

    void static ResetStats(){} // resets all static counters to zero
    Tracer() {} // Default constructor
    Tracer(const std::string& name) {}  // Constructor with string argument
    Tracer(const Tracer& other) {}  // Copy constructor
    Tracer(Tracer&& other) noexcept {}  // Move constructor
    Tracer& operator=(const Tracer& other) {
        copy_assign++;
        if(this != &other) {
            name = other.name;
        }
        return *this;
    }
    Tracer& operator=(const Tracer&& other) noexcept {
        move_assign++;
        if(this != &other) {
            name = std::move(other.name);
            // Дописать очистку полей. Объект должен быть консистентным.
        }
        return *this;
    }
    ~Tracer() {}  // Destructor
    // Methods
    int Id(){}  // returns the id of the object
    const std::string& Name(){} // returns the linked name of the object
    const char* Data(){} // returns the linked name of the object
};

// Static member initialization
int Tracer::counter = 0;
int Tracer::default_ctor = 0;
int Tracer::str_ctor = 0;
int Tracer::copy_ctor = 0;
int Tracer::move_ctor = 0;
int Tracer::copy_assign = 0;
int Tracer::move_assign = 0;
int Tracer::dtor = 0;
int Tracer::alive = 0;

// Reset counters
void Tracer::ResetStats() {
    counter = 0;
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0;
}

// Default constructor
Tracer::Tracer() {
    this->id = ++counter;
    this->name = "obj_" + std::to_string(this->id);
    ++default_ctor;
    ++alive;
}

// Constructor with string argument
Tracer::Tracer(const std::string& name) {
    this->id = ++counter;
    this->name = name + "_" + std::to_string(this->id);
    ++str_ctor;
    ++alive;
}

// Copy constructor
Tracer::Tracer(const Tracer& other) :name(other.name) {
    this->id = ++counter;
    ++copy_ctor;
    ++alive;
}

// Move constructor
Tracer::Tracer(Tracer&& other) noexcept :name(std::move(other.name)) {
    this->id = ++counter;
    ++move_ctor;
    ++alive;
}

// Copy assignment operator
Tracer& operator=(const Tracer& other) {

}

// Move assignment operator
Tracer& operator=(const Tracer& other) noexcept {
    
}

// Destructor
Tracer::~Tracer() {
    ++dtor;
    --alive;
}