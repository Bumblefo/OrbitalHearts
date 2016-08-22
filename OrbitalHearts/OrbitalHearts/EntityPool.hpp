#ifndef ENTITYPOOL_HPP
#define ENTITYPOOL_HPP

#include <vector>

template<class T> class EntityPool
{
public:
	//Constructors/Destructor
	~EntityPool();
	EntityPool(int min_entities = 0);

	//Queries
	int empty() { return inUseSize == 0; };
	int inUseSize() { return inUse; };
	int reservesSize() { return reserves };

	//Commands
	void update();
	void clear();
	void add();
	void remove();

private:
	class LN {
	public:
		LN() {};
		LN(const LN& ln)
			: value(ln.value), next(ln.next) {}
		LN(T v, LN* n = nullptr)
			: value(v), next(n) {}

		T value;
		LN* next = nullptr;

	};

	LN* reservesFront = nullptr;
	LN* inUseFront = nullptr;

	int reserves = 0;
	int inUse = 0;

	void deactivateEntity();
	void activateReserve(T entity);
	void addReserve();
	void deleteList(LN* front);
};

template<class T>
EntityPool<T>::~EntityPool()
{
	deleteList(reservesFront);
	deleteList(inUseFront);
}

template<class T>
EntityPool<T>::EntityPool(int min_entities = 0)
{
	for (int i = 0; i < min_entities; i++)
	{
		
	}
}

template<class T>
void EntityPool<T>::update()
{

}

template<class T>
void EntityPool<T>::clear()
{

}

template<class T>
void EntityPool<T>::add()
{

}

template<class T>
void EntityPool<T>::remove()
{

}

template<class T>
void EntityPool<T>::deactivateEntity()
{

}

template<class T>
void EntityPool<T>::activateReserve(T entity)
{
	pool.push_back(T(entity));
}

template<class T>
void EntityPool<T>::addReserve()
{
	reservesFront = new LN(T(), reservesFront);

}

template<class T>
void EntityPool<T>::deleteList(LN* front)
{
	while (front != nullptr)
	{
		LN* l = front;
		front = front->next;
		delete l;
	}
}


#endif // ENTITYPOOL_HPP