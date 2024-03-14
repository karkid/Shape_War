#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <atomic>

#include "Entity.h"

typedef std::vector<EntityPtr> Entities;
typedef std::map<std::string, Entities> EntitiesMap;
class EntityManager
{
    Entities m_entities;
    EntitiesMap m_entityMap;
    Entities m_entitiesToAdd;
    size_t m_totalEntity = 0;
    static std::atomic<int> nextId;
    static int getNextId() 
    {
        return nextId++;
    };
    void removeDeadEntities(Entities& entities);
public:
    EntityManager() = default;
    ~EntityManager() = default;
    void update();
    EntityPtr addEntity(const std::string& tag);
    void removeEntity(EntityPtr& entity);
    Entities& getEntities();
    Entities& getEntities(const std::string& tag);
};
inline std::atomic<int> EntityManager::nextId(1);