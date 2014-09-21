///
/// A scene graph
///

#pragma once

#include "Object.h"
#include "ObjectList.h"

#define DF_MAX_ALTITUDE 4      ///< Drawing order 0 to max.

class SceneGraph {

 private:
  ObjectList active_objects;   ///< All active Objects.
  ObjectList solid_objects;    ///< Solid Objects.
  ObjectList visible_objects[DF_MAX_ALTITUDE+1]; ///< Visible Objects.
  ObjectList inactive_objects; ///< All inactive Objects.
  
 public:
	 SceneGraph();
  
  /// Insert Object into SceneGraph.
  int insertObject(Object *p_o);

  /// Remove Object from SceneGraph.
  int removeObject(Object *p_o);

  /// Return all active Objects. Empty list if none.
  ObjectList activeObjects() const
  {
	  return active_objects;
  }

  /// Return all active, solid Objects. Empty list if none.
  ObjectList solidObjects() const
  {
	  return solid_objects;
  }

  /// Return all active, visible Objects at altitude. Empty list if none.
  ObjectList visibleObjects(int altitude) const
  {
	  return visible_objects[altitude];
  }

  /// Return all inactive Objects. Empty list if none.
  ObjectList inactiveObjects() const
  {
	  return inactive_objects;
  }
  
  /// Re-position Object in SceneGraph to new altitude.
  /// Return 0 if ok, else -1.
  int updateAltitude(Object *p_o, int new_alt);

  /// Re-position Object in SceneGraph to new solidness.
  /// Return 0 if ok, else -1.
  int updateSolidness(Object *p_o, Solidness new_solidness);

  /// Re-position Object in SceneGraph to new visibility.
  /// Return 0 if ok, else -1.
  int updateVisible(Object *p_vo, bool new_visible);

  /// Re-position Object in SceneGraph to new activeness.
  /// Return 0 if ok, else -1.
  int updateActive(Object *p_o, bool new_active);
};
