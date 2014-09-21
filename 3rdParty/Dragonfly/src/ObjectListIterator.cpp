#include "ObjectListIterator.h"

ObjectListIterator & ObjectListIterator::operator=(const ObjectListIterator &rhs)
{
	this->index = rhs.index;
	this->p_list = rhs.p_list;
	return *this;
}

Object * ObjectListIterator::currentObject() const
{
	return p_list->p_item[index];
}

void ObjectListIterator::next()
{
	index++;
}

void ObjectListIterator::first()
{
	index = 0;
}

ObjectListIterator::ObjectListIterator(const ObjectList *p_list)
{
	this->p_list = p_list;
}

bool ObjectListIterator::isDone() const
{
	return index >= p_list->count;
}

