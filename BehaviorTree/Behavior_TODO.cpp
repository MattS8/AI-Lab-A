//! \file Behavior_TODO.cpp
//! \brief Implements the <code>fullsail_ai::fundamentals::Behavior</code> abstract class.
//! \author Jeremiah Blanchard with code from Cromwell D. Enage

// #include <queue>   NOTE: Only use if your QueueList is not working
#include <stack>
#include "Behavior.h"
#include "../QueueList/QueueList.h"

namespace fullsail_ai { namespace fundamentals {

	// DO NOT Edit or Use these two variables for any reason, it is for memory leak check purposes only.
	unsigned Behavior::createdCount = 0;
	unsigned Behavior::destroyedCount = 0;

	unsigned Behavior::getCreatedCount()
	{
		return createdCount;
	}

	unsigned Behavior::getDestroyedCount()
	{
		return destroyedCount;
	}

	Behavior::Behavior(char const* _description)
	{
		description = _description;
	}

	char const* Behavior::toString() const
	{
		return description;
	}

	// DO NOT edit this function, it is supposed to just return false
	bool Behavior::isLeaf() const
	{
		return false;
	}

	DLLEXPORT size_t Behavior::getChildCount() const
	{
		return children.size();
	}

	//! \TODO
	//!   - Implement the <code>Behavior</code> methods.
	
	DLLEXPORT Behavior* Behavior::getChild(size_t index)
	{
		if (index >= children.size())
			return nullptr;

		return children[index];
	}

	DLLEXPORT Behavior const* Behavior::getChild(size_t index) const
	{
		if (index >= children.size())
			return nullptr;
	
		return children[index];
	}

	void Behavior::addChild(Behavior* child)
	{
		if (child == nullptr)
			return;

		child->parent = this;
		children.push_back(child);
	}

	void traversePreOrder(const Behavior* current, void(*dataFunction)(Behavior const*))
	{
		if (current == nullptr)
			return;

		dataFunction(current);
		for (int i = 0; i < current->getChildCount(); i++)
		{
			traversePreOrder(current->getChild(i), dataFunction);
		}
	}

	void traversePostOrder(const Behavior* current, void(*dataFunction)(Behavior const*))
	{
		if (current == nullptr)
			return;

		for (int i = 0; i < current->getChildCount(); i++)
		{
			traversePostOrder(current->getChild(i), dataFunction);
		}
		dataFunction(current);
	}

	DLLEXPORT void Behavior::breadthFirstTraverse(void(*dataFunction)(Behavior const*)) const
	{
		QueueList<const Behavior*> queue;
		queue.enqueue(this);
		while (!queue.isEmpty())
		{
			const Behavior* current = queue.getFront();
			dataFunction(queue.getFront());
			for (int i = 0; i < current->getChildCount(); i++)
			{
				queue.enqueue(current->getChild(i));
			}
			queue.remove(current);
		}
	}

	DLLEXPORT void Behavior::preOrderTraverse(void(*dataFunction)(Behavior const*)) const
	{
		traversePreOrder(this, dataFunction);
	}

	DLLEXPORT void Behavior::postOrderTraverse(void(*dataFunction)(Behavior const*)) const
	{
		traversePostOrder(this, dataFunction);
	}


}}  // namespace fullsail_ai::fundamentals
