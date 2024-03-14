#include "Game.h"
#include <fstream>

Game::Game(const std::string &config)
{
    init(config);
}

void Game::upadte()
{
}

void Game::sMovement()
{
    if (m_player->cInput->up)
    {
        m_player->cTransform->pos.y -= m_player->cTransform->velocity.y;
    }
    else if (m_player->cInput->left)
    {
        m_player->cTransform->pos.x -= m_player->cTransform->velocity.x;
    }
    else if (m_player->cInput->down)
    {
        m_player->cTransform->pos.y += m_player->cTransform->velocity.x;
    }
    else if (m_player->cInput->right)
    {
        m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
    }

    if (m_entities.tagCount("bullet"))
    {
        for (auto& bullet : m_entities.getEntities("bullet"))
        {
            bullet->cTransform->pos.x += bullet->cTransform->velocity.x;
            bullet->cTransform->pos.y += bullet->cTransform->velocity.y;
        }
    }

}

void Game::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                m_window.close();
                m_running = false;
                break;
            }
            case sf::Event::KeyPressed:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W:
                        m_player->cInput->up = true;
                        break;
                    case sf::Keyboard::A:
                        m_player->cInput->left = true;
                        break;
                    case sf::Keyboard::S:
                        m_player->cInput->down = true;
                        break;
                    case sf::Keyboard::D:
                        m_player->cInput->right = true;
                        break;
                    default:
                        break;
                }
                break;
            }
            case sf::Event::KeyReleased:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W:
                        m_player->cInput->up = false;
                        break;
                    case sf::Keyboard::A:
                        m_player->cInput->left = false;
                        break;
                    case sf::Keyboard::S:
                        m_player->cInput->down = false;
                        break;
                    case sf::Keyboard::D:
                        m_player->cInput->right = false;
                        break;
                    default:
                        break;
                }
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_player->cInput->shoot = true;
                    spawnBullet(m_player, Vector2(event.mouseButton.x, event.mouseButton.y));
                }
            }
            case sf::Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_player->cInput->shoot = false;
                }
            }         
            default:
                break;
        }
    }
}

void Game::sRender()
{
    m_window.clear();
    for(auto& entity: m_entities.getEntities())
    {
        entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);
        entity->cTransform->angle += 1.0f;
        entity->cShape->circle.setRotation(entity->cTransform->angle);
        m_window.draw(entity->cShape->circle);
    }
    m_window.draw(m_text);
    m_window.display();
}

void Game::sEnemySpawner()
{
    static int i = 0;
    if (i < 10)
    {
        spawnEnemy();
        ++i;
    }

}

void Game::sCollision()
{
}

void Game::init(const std::string &config)
{
    std::ifstream fin(config);
    if (fin.is_open())
    {
        std::string type;
        fin >> type;
        if (type == "Window")
        {
            int W, H, FL, FS;
            fin >> W >> H >> FL >> FS;
            m_window.create(sf::VideoMode(W, H), "Shape War", FS == 1 ? sf::Style::Fullscreen : sf::Style::Default);
            m_window.setFramerateLimit(FL);
            while (fin >> type)
            {
                if (type == "Font")
                {
                    std::string name;
                    int size;
                    int r, g, b;
                    fin >> name >> size >> r >> g >> b;

                    if (!m_font.loadFromFile(name))
                    {
                        std::cerr << "Unable to load font" << std::endl;
                        break;
                    } 
                    m_text.setFont(m_font);
                    m_text.setCharacterSize(size);
                    m_text.setFillColor(sf::Color(r, g, b));
                    m_text.setString("Score : ");
                }
                else if (type == "Player")
                {
                    fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S 
                        >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB 
                        >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB 
                        >> m_playerConfig.OT >> m_playerConfig.V;
                }
                else if (type == "Enemy")
                {
                    fin >> m_enemyConfig.SR   >> m_enemyConfig.CR >> m_enemyConfig.SMIN
                        >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG 
                        >> m_enemyConfig.OB   >> m_enemyConfig.OT >> m_enemyConfig.VMAX 
                        >> m_enemyConfig.VMAX >> m_enemyConfig.L  >> m_enemyConfig.SP;
                }
                else if (type == "Bullet")
                {
                    fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S
                        >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB 
                        >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB 
                        >> m_bulletConfig.OT >> m_bulletConfig.V  >> m_bulletConfig.L;
                }
            }
        }
        else
        {
            std::cerr << "Invalid file";
        }     
        fin.close();
    }
    else
    {
        std::cerr << "Error on opening the file " << config << std::endl;
    } 
    spawnPlayer();
}

void Game::spawnPlayer()
{
    auto entity = m_entities.addEntity("player");

    entity->cTransform = std::make_shared<CTransform>( Vector2(m_window.getSize().x/2, m_window.getSize().y/2),
                                                         Vector2(m_playerConfig.S, m_playerConfig.S),
                                                         Vector2(1.0f,1.0f),
                                                         0.0f );
    entity->cShape = std::make_shared<CShape>( m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB)
                                                ,sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB)
                                                ,m_playerConfig.OT);
    entity->cInput = std::make_shared<CInput>();
    entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

    m_player = entity;
}

void Game::spawnEnemy()
{
    auto entity = m_entities.addEntity("enemy");

    float ex = rand() % m_window.getSize().x;
    float ey = rand() % m_window.getSize().y;

    float es = (rand() / (float) m_enemyConfig.SMAX) * (m_enemyConfig.SMAX  - m_enemyConfig.SMIN);
    int v = m_enemyConfig.VMIN + (rand() %(1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN));

    entity->cTransform = std::make_shared<CTransform>( Vector2(ex, ey),
                                                        Vector2(es, es),
                                                        Vector2(1.0f,1.0f),
                                                        0.0f );
    
    entity->cShape = std::make_shared<CShape>( m_enemyConfig.SR, v, sf::Color(rand()%255, rand()%255, rand()%255)
                                               ,sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB)
                                               ,m_enemyConfig.OT);
    entity->cInput = std::make_shared<CInput>();
    entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
    entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
}

void Game::spawnBullet(EntityPtr source_entity, Vector2 target)
{
    auto entity = m_entities.addEntity("bullet");

    Vector2 pos(source_entity->cShape->circle.getPosition().x, source_entity->cShape->circle.getPosition().y);
    Vector2 dir = target - pos;
    dir.normalize();
    Vector2 speed = dir * Vector2(m_bulletConfig.S, m_bulletConfig.S);
    entity->cTransform = std::make_shared<CTransform>( pos, speed, Vector2(1.0f,1.0f), 0.0f );
    entity->cShape = std::make_shared<CShape>( m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB)
                                               ,sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB)
                                               ,m_bulletConfig.OT);
    entity->cInput = std::make_shared<CInput>();
    entity->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
    entity->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
}

void Game::run()
{
    while ((m_running))
    {
        if (m_window.isOpen())
        {
            m_entities.update();
            if (!m_paused)
            {
                sEnemySpawner();
                sMovement();
                sCollision();
                sUserInput();
            }
            sRender();
        }
        else
        {
            break;
        }
    }
}

void Game::setPaused(bool paused)
{
    m_paused = paused;
}
