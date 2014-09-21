#include "SceneGraph.h"

int SceneGraph::removeObject(Object *p_o)
{
	active_objects.remove(p_o);
	return 0;
}

int SceneGraph::insertObject(Object *p_o)
{
	active_objects.insert(p_o);
	return 0;
}

SceneGraph::SceneGraph()
{

}

