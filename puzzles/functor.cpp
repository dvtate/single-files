#include<iostream>
#include <vector>
#include <variant>
#include <memory>



// abstract functor type 
class Functor {
public:
	virtual ~Functor(){};
	virtual int operator()(int) = 0;
};

class Add : public virtual Functor {
public:
	int lhs;
	Add(int lhs): lhs(lhs) {}
	int operator()(int rhs) {
		return lhs + rhs;
	}
};


class Sub : public virtual Functor {
public:
	int lhs;
	Sub(int lhs): lhs(lhs) {}
	int operator()(int rhs) {
		return lhs - rhs;
	}
};

int main() {
	Add* add = new Add(5);
	Sub sub(10);

	std::unique_ptr<Functor> fptr(new Sub(sub));
	std::cout <<&add <<std::endl;
	std::cout <<(Functor*) &add <<std::endl;
	std::vector<Functor*> ops { add, &sub };
	// can only have pointers to abstract types
	Functor& a = *add;
	Functor& b = sub;
	
	int i;
	std::cin >>i;
	std::cout <<a(b(i)) <<std::endl;
	
	delete ops[0];

}
