template <typename T>
class Base {
public:
	virtual void get(T data) {
		std::cout << "Base class: " << data << std::endl;
	}
	virtual void set(T data) {
    	
	}
	virtual ~Base() = default;
};

template <typename T>
class Derived : public Base<T> {
public:
    void get(T data) override {
        std::cout << "Derived class: " << data << std::endl;
    }
};

