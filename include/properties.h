#pragma once


template <typename T>
class Properties_T {
public:
	virtual void get(T data) {
		std::cout << "Base class: " << data << std::endl;
	}
	virtual void set(T data) {
    	
	}
	virtual ~Base() = default;
};

template <typename T>
class Properties : public Properties_T<T> {
public:
	Properties (const Properties&) = delete;
	Properties& operator=(const Properties&) = delete;
	
	void get(T data) override {
		std::cout << "Derived class: " << data << std::endl;
	}

	void set(T data) {
    	
	}

};

