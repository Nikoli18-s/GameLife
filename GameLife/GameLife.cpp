#include <iostream>
#include <SFML/Graphics.hpp>

// =============================================================================

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

// =============================================================================

class m_field
{
private:

    unsigned int m_cells[WIDTH][HEIGHT];

public:

    m_field() 
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
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game of Life");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }
    return 0;
}