#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Vector2.h"


struct CCollision
{
    float radius = 0.0f;
    CCollision(float _radius = 0.0f): radius(_radius) {}
};
typedef std::shared_ptr<CCollision> CCollisionPtr;

struct CScore
{
    int score = 0;
    CScore(int _score = 0): score(_score){}
};
typedef std::shared_ptr<CScore> CScorePtr;

struct CTransform
{
    Vector2 pos;
    Vector2 velocity;
    Vector2 scale;
    double angle = 0.0f;
    CTransform(Vector2 _pos, Vector2 _velocity, Vector2 _scale, double _angle)
        : pos(_pos), velocity(_velocity), scale(_scale), angle(_angle)
    {
    }
};
typedef std::shared_ptr<CTransform> CTransformPtr;

struct CShape
{
    sf::CircleShape circle;

    CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, double thickness)
        : circle(radius, points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
    }
};
typedef std::shared_ptr<CShape> CShapePtr;

struct CInput
{
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;
};
typedef std::shared_ptr<CInput> CInputPtr;

struct CLifespan
{
    int remaining = 0;
    int total = 0;
    CLifespan(int _total) : total(_total), remaining(_total) {}
};
typedef std::shared_ptr<CLifespan> CLifespanPtr;