#include "ObjectList.h"

ObjectList ObjectList::operator+(ObjectList second_list)
{
// 	if ((count + second_list.count) > max_count)
// 	{
// 		fprintf(stderr, "ObjectList: Fatal Error: Object List combine operation exceeded max count.\n");
// 	}
// 	else
// 	{
// 		auto newlist = ObjectList(*this);
// 
// 		memcpy(&p_item[count], second_list.p_item, sizeof(Object*)* second_list.count);
// 	}
// 
 	return *this;
}

void ObjectList::clear()
{
	for (int i = 0; i < max_count ; i++)
	{
		if (p_item[i] != nullptr)
		{
			delete p_item[i];
			p_item[i] = nullptr;
		}
	}
}

int ObjectList::remove(Object *p_o)
{
	for (int i = 0; i < count; i++)
	{
		if (p_item[i] == p_o)
		{
			p_item[i] = nullptr;
			count--;

			//sort the objects
			int i;
			int openSlot = -1;
			for (i = 0; i < max_count; i++)
			{
				if (openSlot == -1 && p_item[i] == nullptr)
				{
					openSlot = i;
				}
				else if (openSlot != -1 && p_item[i] != nullptr)
				{
					p_item[openSlot] = p_item[i];
					p_item[i] = nullptr;
					openSlot = i;
				}
			}
			return 0;
		}
	}


	return -1;
}

int ObjectList::insert(Object *p_o)
{
	for (int i = 0; i <= count; i++)
	{
		if (p_item[i] == p_o)
		{
			return -1;
		}
	}

	for (int i = 0; i <= count; i++)
	{
		if (p_item[i] == nullptr)
		{
			p_item[i] = p_o;
			count++;
			return 0;
		}
	}

	return -1;
}

ObjectList & ObjectList::operator=(const ObjectList &rhs)
{
	p_item = (Object**)malloc(sizeof(Object*)* max_count);
	memcpy(p_item, rhs.p_item, sizeof(Object*)* max_count);

	return *this;
}

ObjectList::ObjectList(const ObjectList &other)
{
	count = other.count;
	max_count = other.max_count;
	p_item = (Object**)malloc(sizeof(Object*)* max_count);
	memcpy(p_item, other.p_item, sizeof(Object*)* max_count);
}

ObjectList::ObjectList()
{
	p_item = (Object**)malloc(sizeof(Object*)* max_count);
	memset(p_item, NULL, sizeof(Object*)* max_count);
}

ObjectList::~ObjectList()
{
	free(p_item);
}

