//! \file QueueList_TODO.h
//! \brief Defines the <code>fullsail_ai::data_structures::QueueList</code> class template
//! implementation.
//! \author Cromwell D. Enage
#ifndef _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_
#define _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

namespace fullsail_ai { namespace fundamentals {

	//! \TODO
	//!   - Complete the definition of the <code>QueueList::Iterator</code> pre-increment operator.
	//!   - Complete the definition of the <code>QueueList::Iterator</code> dereference operator.
	//!   - Define the <code>QueueList</code> constructor.
	//!   - Define the <code>QueueList</code> destructor.
	//!   - Define the <code>QueueList</code> methods.

	template<typename T>
	inline QueueList<T>::QueueList()
	{
		front = back = nullptr;
	}

	template<typename T>
	inline QueueList<T>::~QueueList()
	{
		removeAll();
	}

	template <typename T>
	typename QueueList<T>::Iterator& QueueList<T>::Iterator::operator++()
	{
		if (this->currentNode != nullptr)
			this->currentNode = this->currentNode->next;
		return *this;
	}

	template <typename T>
	T QueueList<T>::Iterator::operator*() const
	{
		return this->currentNode->data;
	}

	template<typename T>
	inline bool QueueList<T>::isEmpty() const
	{
		return front == nullptr;
	}

	template<typename T>
	inline void QueueList<T>::enqueue(T element)
	{
		// Create new node
		Node* newNode = new Node(element);
		newNode->next = nullptr;

		if (isEmpty())
			front = back = newNode;
		else 
		{
			back->next = newNode;
			back = newNode;
		}
	}

	template<typename T>
	inline T QueueList<T>::getFront() const
	{
		return front->data;
	}

	template<typename T>
	inline void QueueList<T>::dequeue()
	{
		if (front == nullptr)
			return;

		Node* tempNode = front;
		front = front->next;
		delete tempNode;

		// Set back to null if last item was dequeued
		if (front == nullptr)
			back = nullptr;
	}

	template<typename T>
	inline void QueueList<T>::removeAll()
	{
		while (front != nullptr)
		{
			dequeue();
		}
	}

	template<typename T>
	inline bool QueueList<T>::contains(T element) const
	{
		for (auto it = this->begin(); it != this->end(); it++)
		{
			if (*it == element)
				return true;
		}

		return false;
	}

	template<typename T>
	inline void QueueList<T>::remove(T element)
	{
		if (isEmpty())
			return;

		Node* parent = front;
		Node* current = front;
		Node* tempNode;
		while (current != nullptr)
		{
			if (current->data == element)
			{
				// Remove Front
				if (current == front)
				{
					tempNode = front;
					front = front->next;
					if (front == nullptr)
						back = nullptr;
					delete tempNode;
					return;
				}

				// Remove Back
				if (current == back)
				{
					delete back;
					back = parent;
					back->next = nullptr;
					return;
				}

				// Remove Middle
				tempNode = current;
				parent->next = tempNode->next;
				delete tempNode;
				return;
			}

			parent = current;
			current = current->next;
		}
	}


}}  // namespace fullsail_ai::fundamentals

#endif  // _FULLSAIL_AI_FUNDAMENTALS_QUEUELIST_TODO_H_

