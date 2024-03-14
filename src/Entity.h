#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "Components.h"

class EntityManager;

class Entity
{
    friend class EntityManager;
    size_t m_id = -1;
    bool m_active = true;
    std::string m_tag = "";

    Entity(size_t id, const std::string& tag);
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;
public:
    ~Entity() = default;
    CTransformPtr cTransform;
    CCollisionPtr cCollision;
    CShapePtr cShape;
    CInputPtr cInput;
    CScorePtr cScore;
    CLifespanPtr cLifespan;
    
    void destroy();
    bool isActive() const;
    std::string tag() const;
    size_t id() const;
};
typedef std::shared_ptr<Entity> EntityPtr;