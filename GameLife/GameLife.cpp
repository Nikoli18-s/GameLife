#include <iostream>
#include <SFML/Graphics.hpp>

// =============================================================================

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// =============================================================================

class Field
{
private:

    char m_cells[WIDTH][HEIGHT];

public:

    Field() 
    {
        for (int i = 0; i < WIDTH; i++)
            for (int j = 0; j < HEIGHT; j++)
                m_cells[i][j] = 0;
    }

    const unsigned int get_cell_state(const unsigned int x, const unsigned int y)
    {
       return m_cells[x][y];
    }

    void set_cell(const unsigned int x, const unsigned int y)
    {
        m_cells[x][y] = 1;
    }

    void reset_cell(const unsigned int x, const unsigned int y)
    {
        m_cells[x][y] = 0;
    }

    unsigned int sum_around_cell(const unsigned int x, const unsigned int y)
    {
        unsigned int sum = 0;
        if (x == 0)
        {
            if (y == 0)
            {
                sum += get_cell_state(0, 1);
                sum += get_cell_state(1, 0);
                sum += get_cell_state(1, 1);
            }
            else if (y == HEIGHT - 1)
            {
                sum += get_cell_state(0, HEIGHT - 2);
                sum += get_cell_state(1, HEIGHT - 2);
                sum += get_cell_state(1, HEIGHT - 1);
            }
            else
            {
                sum += get_cell_state(0, y - 1);
                sum += get_cell_state(0, y + 1);
                sum += get_cell_state(1, y - 1);
                sum += get_cell_state(1, y);
                sum += get_cell_state(1, y + 1);
            }
        }
        else if (x == WIDTH - 1)
        {
            if (y == 0)
            {
                sum += get_cell_state(WIDTH - 1, 1);
                sum += get_cell_state(WIDTH - 2, 0);
                sum += get_cell_state(WIDTH - 2, 1);
            }
            else if (y == HEIGHT - 1)
            {
                sum += get_cell_state(WIDTH - 2, HEIGHT - 2);
                sum += get_cell_state(WIDTH - 2, HEIGHT - 1);
                sum += get_cell_state(WIDTH - 1, HEIGHT - 2);
            }
            else
            {
                sum += get_cell_state(WIDTH - 2, y - 1);
                sum += get_cell_state(WIDTH - 2, y);
                sum += get_cell_state(WIDTH - 2, y + 1);
                sum += get_cell_state(WIDTH - 1, y - 1);
                sum += get_cell_state(WIDTH - 1, y + 1);
            }
        }
        else
        {
            if (y == 0)
            {
                sum += get_cell_state(x - 1, 0);
                sum += get_cell_state(x - 1, 1);
                sum += get_cell_state(x, 1);
                sum += get_cell_state(x + 1, 0);
                sum += get_cell_state(x + 1, 1);
            }
            else if (y == HEIGHT - 1)
            {
                sum += get_cell_state(x - 1, HEIGHT - 2);
                sum += get_cell_state(x - 1, HEIGHT - 1);
                sum += get_cell_state(x, HEIGHT - 2);
                sum += get_cell_state(x + 1, HEIGHT - 2);
                sum += get_cell_state(x + 1, HEIGHT - 1);
            }
            else
            {
                sum += get_cell_state(x - 1, y - 1);
                sum += get_cell_state(x - 1, y);
                sum += get_cell_state(x - 1, y + 1);
                sum += get_cell_state(x, y - 1);
                sum += get_cell_state(x, y + 1);
                sum += get_cell_state(x + 1, y - 1);
                sum += get_cell_state(x + 1, y);
                sum += get_cell_state(x + 1, y + 1);
            }
        }
        return sum;
    }

    void update()
    {
        for (int i = 0; i < WIDTH; i++)
            for (int j = 0; j < HEIGHT; j++)
            {
                switch (sum_around_cell(i, j))
                {
                case 3:
                    set_cell(i, j);
                    break;
                case 2:
                    break;
                default:
                    reset_cell(i, j);
                    break;
                }
            }
    }

    ~Field() { }
};

// =============================================================================

class Presenter
{
private:

    sf::RenderWindow m_window;

    Field m_field;

public:

    Presenter() :
        m_window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar),
        m_field() {}

    void review()
    {

        sf::Event event;

        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                m_field.set_cell(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
                std::cout << sf::Mouse::getPosition(m_window).x << sf::Mouse::getPosition(m_window).y << std::endl;
                break;
            case sf::Event::KeyPressed:
                handle_key_pressed(event.key.code);
                std::cout << "space" << std::endl;
                break;
            default:
                break;
            }
        }
    }

    void handle_key_pressed(const sf::Keyboard::Key code)
    {
        switch (code)
        {
        case sf::Keyboard::Space:
            m_field.update();
            break;
        default:
            break;
        }
    }

    void render()
    {
        sf::Vertex cell;

        m_window.clear();

        for (int i = 0; i < WIDTH; i++)
            for (int j = 0; j < HEIGHT; j++)
            {
                cell.position = sf::Vector2f(i, j);
                if (m_field.get_cell_state(i, j))
                    cell.color = sf::Color::White;
                else
                    cell.color = sf::Color::Black;

                m_window.draw(&cell, 1, sf::Points);
            }
               
        m_window.display();
    }

    void run()
    {
        while (m_window.isOpen())
        {
            review();
            render();
        }
    }

    ~Presenter() {}
};

int main()
{
    Presenter m_presenter;
    m_presenter.run();

    return 0;
}