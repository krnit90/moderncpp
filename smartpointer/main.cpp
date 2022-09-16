#include "CUniquePtr.h"
#include "CSharedPtr.h"

class Test
{
public:
	Test(int a) :i(a) {}
	void display()
	{
		std::cout << " Hello Display " << i << std::endl;
	}
private:
	int i;
};

void Test_uniqueptr()
{
	CUniquePtr <Test> ptr;
	CUniquePtr <Test> p(new Test(1));
	p.get()->display();
	p.release();
	p.reset(new Test(2));
	p->display();
	std::cout << std::endl;
}

void Test_sharedptr()
{
	CSharedPtr <Test> p;
	CSharedPtr <Test> ptr1(new Test(3));
	std::cout << ptr1.useCount() << std::endl;

	CSharedPtr <Test>  ptr2 = ptr1;
	CSharedPtr <Test> ptr3(new Test(4));
	ptr3 = ptr2;
	std::cout << ptr1.useCount() << std::endl;

	CSharedPtr <Test> ptr4(new Test(3));
	ptr4 = std::move(ptr3);
	std::cout << ptr3.useCount() << std::endl;

	CSharedPtr <Test> ptr5(std::move(ptr1));
	std::cout << ptr1.useCount() << std::endl;
}
int main()
{
	Test_uniqueptr();
	Test_sharedptr();
	return 0;
}