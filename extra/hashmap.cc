#include <unordered_map>

template <typename T>
class Base {
	std::unordered_map<std::string, std::string> map;
	
public:
	virtual void set(T data) {
		std::cout << "Base class: " << data << std::endl;
	}

    virtual void get(std::string key, T data) {
        std::cout << "Base class: " << data << std::endl;
    }
    virtual ~Base() = default;
};

template <typename T>
class Derived : public Base<T> {
public:
    void process(T data) override {
        std::cout << "Derived class: " << data << std::endl;
    }
};

int main() {
    Base<int>* baseInt = new Derived<int>();
    baseInt->process(10); // Output: Derived class: 10
    delete baseInt;

    Base<std::string>* baseString = new Derived<std::string>();
    baseString->process("Hello"); // Output: Derived class: Hello
    delete baseString;
    
    return 0;
}
