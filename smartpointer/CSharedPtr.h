#pragma once
#include <iostream>

template<class T>
class CSharedPtr
{
public:
	CSharedPtr() :ptr(nullptr) {}

	CSharedPtr(T* _ptr) : ptr(_ptr) {
		refCount = new std::size_t{ 1 };
	}

	CSharedPtr(CSharedPtr& _ptr) :ptr(_ptr.get()) {
		refCount = _ptr.refCount;
		incRefCount();
	}

	CSharedPtr(CSharedPtr&& _ptr) {
		ptr = std::move(_ptr.ptr);
		refCount = std::move(_ptr.refCount);
		_ptr.ptr = nullptr;
		_ptr.refCount = 0;
	}

	CSharedPtr& operator= (CSharedPtr&& _ptr) {
		if (ptr) {
			delete[] ptr;
			delete refCount;
			ptr = nullptr;
			refCount = nullptr;
		}
		ptr = std::move(_ptr.ptr);
		refCount = std::move(_ptr.refCount);
		_ptr.ptr = nullptr;
		_ptr.refCount = 0;

		std::cout << "move Ref count=" << *refCount << std::endl;
		return *this;
	}

	CSharedPtr& operator= (CSharedPtr& _ptr) {
		if (ptr) {
			delete[] ptr;
			delete refCount;
		}
		ptr = _ptr.get();
		refCount = _ptr.refCount;
		incRefCount();
		std::cout << "Ref count=" << *refCount << std::endl;
		return *this;
	}

	~CSharedPtr() {
		release();
	}

	auto  useCount()const -> size_t {
		if (refCount)
			return *refCount;
		return 0;
	}

	T* get() {
		return ptr;
	}

	T& operator *()
	{
		return *get();
	}

	T* operator ->()
	{
		return get();
	}
private:

	auto incRefCount() -> size_t {
		return ++ * refCount;
	}

	void release()
	{
		if (refCount == nullptr)
			return;
		std::cout << "release Ref count=" << *refCount << std::endl;
		if (*refCount == 0)
		{
			delete[] ptr;
			delete refCount;
		}
		else
			--* refCount;
	}

	T* ptr;
	size_t* refCount = 0;
};