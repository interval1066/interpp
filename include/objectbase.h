#include <unordered_map>

namespace storage
{
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
}

