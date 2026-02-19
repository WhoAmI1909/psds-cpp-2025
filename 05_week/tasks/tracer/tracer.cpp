#include <string>


class Tracer {
    int id;             // unique identifier of the object
    std::string name;   // name of the object

public:
    static size_t count;         // number of created objects
    static size_t default_ctor;    // number of calls to default constructor
    static size_t str_ctor;        // number of calls to constructor with string argument
    static size_t copy_ctor;       // number of calls to copy constructor
    static size_t move_ctor;       // number of calls to move constructor
    static size_t copy_assign;     // number of calls to copy assignment operator
    static size_t move_assign;     // number of calls to move assignment operator
    static size_t dtor;            // number of calls to destructor
    static size_t alive;           // number of currently alive objects

    void static ResetStats(); // resets all static counters to zero
    Tracer(); // Default constructor
    Tracer(const std::string&);  // Constructor with string argument
    Tracer(const Tracer&);  // Copy constructor
    Tracer(Tracer&&) noexcept;  // Move constructor
    Tracer& operator=(const Tracer&);
    Tracer& operator=(Tracer&&) noexcept;
    ~Tracer();  // Destructor
    // Methods
    int Id() const noexcept;  // returns the id of the object
    const std::string& Name() const noexcept; // returns the linked name of the object
    const char* Data() const noexcept; // returns the linked name of the object
};

// Static member initialization
size_t Tracer::count = 0;
size_t Tracer::default_ctor = 0;
size_t Tracer::str_ctor = 0;
size_t Tracer::copy_ctor = 0;
size_t Tracer::move_ctor = 0;
size_t Tracer::copy_assign = 0;
size_t Tracer::move_assign = 0;
size_t Tracer::dtor = 0;
size_t Tracer::alive = 0;

// Reset counters
void Tracer::ResetStats() {
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0;
    count = 0;
}

// Default constructor
Tracer::Tracer()
    : id(++count),
    name("obj_" + std::to_string(id))
{
    ++default_ctor;
    ++alive;
}

// Constructor with string argument
Tracer::Tracer(const std::string& name)
    : id(++count),
    name(name + "_" + std::to_string(id))
{
    ++str_ctor;
    ++alive;
}

// Copy constructor
Tracer::Tracer(const Tracer& other)
    : id(++count),
    name(other.name)
{
    ++copy_ctor;
    ++alive;
}

// Move constructor
Tracer::Tracer(Tracer&& other) noexcept
    : id(++count),
    name(std::move(other.name))
{
    ++move_ctor;
    ++alive;
}

// Copy assignment operator
Tracer& Tracer::operator=(const Tracer& other) {
    if(this != &other) {
        name = other.name;
        copy_assign++;
    }
    return *this;
}

// Move assignment operator
Tracer& Tracer::operator=(Tracer&& other) noexcept {
    if(this != &other) {
        name = std::move(other.name);
        move_assign++;
    }
    return *this;
}

// Destructor
Tracer::~Tracer() {
    ++dtor;
    --alive;
}

// Methods
int Tracer::Id() const noexcept {
    return id;
}

const std::string& Tracer::Name() const noexcept {
    return name;
}

const char* Tracer::Data() const noexcept {
    return name.c_str();
}