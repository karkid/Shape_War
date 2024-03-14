#include "EntityManger.h"

void EntityManager::removeDeadEntities(Entities& entities)
{
    entities.erase(
        std::remove_if(entities.begin(), entities.end(), [](const EntityPtr& ePtr) {
            return !ePtr->isActive();
        }),
        entities.end()
    );
}


void EntityManager::update()
{
    for(auto& entity: m_entitiesToAdd)
    {
        m_entities.push_back(entity);
        if (m_entityMap.find(entity->tag()) == m_entityMap.end())
        {
            m_entityMap[entity->tag()] = Entities();
        }

        m_entityMap.at(entity->tag()).push_back(entity);
    }

    removeDeadEntities(m_entities);

    for (auto& [tag, entities] : m_entityMap)
    {
        removeDeadEntities(entities);
    }
    m_entitiesToAdd.clear();
}

EntityPtr EntityManager::addEntity(const std::string &tag)
{
    auto ePtr = std::shared_ptr<Entity>(new Entity(EntityManager::getNextId(), tag));
    m_entitiesToAdd.push_back(ePtr);
    return ePtr;
}

Entities &EntityManager::getEntities()
{
    return m_entities;
}

bool EntityManager::tagCount(const std::string &tag) const
{
    return m_entityMap.count(tag);
}

Entities &EntityManager::getEntities(const std::string &tag)
{
    return m_entityMap.at(tag);
}

void EntityManager::removeEntity(EntityPtr &entity)
{
    entity->m_active = false;
}
