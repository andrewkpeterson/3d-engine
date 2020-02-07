#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <map>

#include "src/engine/common/component/Component.h"
#include "src/engine/util/TypeMap.h"

class Component;
class GameWorld;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    template <typename Comp>
    void addComponent(std::shared_ptr<Comp> &&c) {
      comps.put<Comp>(std::forward<std::shared_ptr<Comp>>(c));
    }
    void removeComponent(std::string name);
    template <typename Comp>
    Comp* getComponent() {
        auto it = comps.find<Comp>();
        assert(it != comps.end());
        return static_cast<Comp*>(it->second.get());
    }
    //void addComponent(std::shared_ptr<Component> component);
    //std::shared_ptr<Component> getComponent(std::string name);
    void addComponentsToSystems();
    void removeComponentsFromSystems();
    GameWorld *getGameWorld();

private:
    std::map<std::string, std::shared_ptr<Component>> m_components;
    TypeMap<std::shared_ptr<Component>> comps;
    GameWorld *m_gw;

};

#endif // GAMEOBJECT_H
