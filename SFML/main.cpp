
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Create main window
    // sf::RenderWindow App(sf::VideoMode(640, 480), "SFML Graphics", sf::Style::Fullscreen);
    sf::RenderWindow App(sf::VideoMode(640, 480), "SFML Graphics");
    
    int circleX = 200;
    int circleY = 200;
    
    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
            // Text
            else if (Event.Type == sf::Event::KeyPressed)
            {
                if (Event.Key.Code == 'q'){
                    App.Close();
                }
                else if (Event.Key.Code == 'a'){
                    circleX -= 50;
                }
                else if (Event.Key.Code == 'd'){
                    circleX += 50;
                }
                else if (Event.Key.Code == 'w'){
                    circleY -= 50;
                }
                else if (Event.Key.Code == 's'){
                    circleY += 50;
                }
            }
        }

        // Clear screen
        App.Clear();

        // Draw apredefined shape
        App.Draw(sf::Shape::Circle(circleX, circleY, 100, sf::Color::Yellow, 10, sf::Color::Blue));

        // Finally, display the rendered frame on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}
