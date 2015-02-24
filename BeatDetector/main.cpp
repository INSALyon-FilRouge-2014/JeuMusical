#include "SoundManager.h"
#include "Scene.h"
#include "BeatDetector.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>


int main(int argc, char *argv[])
{
    // Create main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "Beat detector");
    App.SetPosition(0, 0);
    App.ShowMouseCursor(true);

    // Create SoundManager
    SoundManager* snd_mng = new SoundManager();
    snd_mng->load_song(argv[1]); // load song in arguments
    snd_mng->play();
    snd_mng->pause();

    // Create BeatDetector
    BeatDetector* beatdec = new BeatDetector(snd_mng);
    beatdec->audio_process(); // launch beats detection

    // Create Scene
    Scene Scene(&App, snd_mng, beatdec, argv[1]);

    // Set View
    sf::Vector2f Center(0, 0);
    sf::Vector2f HalfSize(400, 300);
    sf::View View(Center, HalfSize);
    App.SetView(View);

    bool ctrl_pressed=false; // mémorise l'appui sur Ctrl
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed) App.Close();
            if (Event.Type == sf::Event::KeyPressed)
            {
                if (Event.Key.Code == sf::Key::LControl) ctrl_pressed=true;
                if (ctrl_pressed==true)
                {
                    if (Event.Key.Code == sf::Key::Left) Scene.shift(200000);
                    if (Event.Key.Code == sf::Key::Right) Scene.shift(-200000);
                    if (Event.Key.Code == sf::Key::Down) Scene.extend(860);
                    if (Event.Key.Code == sf::Key::Up) Scene.extend(-860);
                    if (Event.Key.Code == sf::Key::H) snd_mng->change_pitch(0.01f);
                    if (Event.Key.Code == sf::Key::J) snd_mng->change_pitch(-0.01f);
                }
                else
                {
                    if (Event.Key.Code == sf::Key::Left) Scene.shift(10000);
                    if (Event.Key.Code == sf::Key::Right) Scene.shift(-10000);
                    if (Event.Key.Code == sf::Key::Down) Scene.extend(43);
                    if (Event.Key.Code == sf::Key::Up) Scene.extend(-43);
                    if (Event.Key.Code == sf::Key::Add) snd_mng->change_pitch(0.1f);
                    if (Event.Key.Code == sf::Key::Subtract) snd_mng->change_pitch(-0.1f);
                }

                if (Event.Key.Code == sf::Key::P) snd_mng->pause();
                if (Event.Key.Code == sf::Key::R) snd_mng->reset();
            }
            if (Event.Type == sf::Event::KeyReleased)
            {
                if (Event.Key.Code == sf::Key::LControl) ctrl_pressed=false;
            }
            if (Event.Type == sf::Event::MouseButtonPressed)
            {
                if (Event.MouseButton.Button == sf::Mouse::Left) Scene.goto_pos(Event.MouseButton.X);
            }
        }

        // Clear screen
        App.Clear(sf::Color(0,0,0));

        // Draw Scene
        Scene.draw();

        // Display
        App.Display();
    }
    return EXIT_SUCCESS;
}
