#pragma once

#include <SFML/Graphics.hpp>

#include "EntityManger.h"

struct PlayerConfig 
{ 
    int SR; // Shape Radius
    int CR; // Collision Radius
    int FR; // Fill color red
    int FG; // Fill color green
    int FB; // FIll color blue
    int OR; // Outline color red 
    int OG; // Outline color green
    int OB; // Outline color blue
    int OT; // Outline thickness
    int V;  // Shape Vertices
    float S; // Speed
};
struct EnemyConfig  
{ 
    int SR; // Shape radius
    int CR; // Collision radius
    int OR; // Outline color red
    int OG; // Outline color green
    int OB; // Outline color blue
    int OT; // Outline thickness
    int VMIN; // Min Vertices
    int VMAX; // Max Vertices
    int L; // Lifespan
    int SP; // Spawan Interval
    float SMIN; // Min speed
    float SMAX; // Max speed
};
struct BulletConfig { 
    int SR; // Shape Radius
    int CR; // Collision Radius
    int FR; // Fill color red
    int FG; // Fill color green
    int FB; // FIll color blue
    int OR; // Outline color red
    int OG; // Outline color gree
    int OB; // Outline color blue
    int OT; // Outline thickness
    int V;  // Shape Vertices
    int L; // Lifespan
    float S; // Speed
};

class Game
{
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    bool m_paused = false;
    bool m_running = true;

    std::shared_ptr<Entity> m_player;

    void sMovement();
    void sUserInput();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void init(const std::string& config);
    void spawnPlayer();
    void spawnEnemy();
    void spawnBullet(EntityPtr source_entity, Vector2 target);
public:
    Game(const std::string& config);
    ~Game() = default;
    void upadte();
    void run();
    void setPaused(bool paused);
};
