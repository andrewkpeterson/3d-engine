#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <map>

#include "src/engine/common/component/Component.h"
#include "src/engine/util/TypeMap.h"

class Component;
class GameWorld;

/**
 * To properly create a GameObject, we first make a shared_ptr<GameObject>. Next, we
 * create components and add those components to the GameObject. Finally, we add the
 * object to the GameWorld. The Components of the GameObject indicate which systems
 * the GameObject's components will be added to.
 *
 * To remove a GameObject from the GameWorld, we call the GameWorld's removeGameObject
 * method. This will also remove the GameObject's components from the GameWorld's
 * systems.
 */
class GameObject
{
public:
    GameObject(std::string id="");
    ~GameObject();

    template <typename Comp>
    void addComponent(std::shared_ptr<Comp> &&c) {
        m_components.put<Comp>(std::forward<std::shared_ptr<Comp>>(c));
        auto it = m_components.find<Comp>();
        std::dynamic_pointer_cast<Comp>(it->second)->setGameObject(this);
    }

    template <typename Comp>
    void removeComponent() {
        m_components.remove<Comp>();
    }

    template <typename Comp>
    std::shared_ptr<Comp> getComponent() {
        auto it = m_components.find<Comp>();
        assert(it != m_components.end());
        return std::dynamic_pointer_cast<Comp>(it->second);
    }

    void addSelfToSystems();
    void removeSelfFromSystems();
    void removeAllComponents();
    GameWorld *getGameWorld();
    void setGameWorld(GameWorld *gameworld);
    std::string getID();

private:
    TypeMap<std::shared_ptr<Component>> m_components;
    GameWorld *m_gw;
    std::string m_id;
    static int nextID;

};

#endif // GAMEOBJECT_H
