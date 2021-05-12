#include "Pong.h"
#include <stdio.h>
#include <SDL_mixer.h>

SDL_Window* windows = NULL;
SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8* wavBuffer;


bool Pong::Init(SDL_Renderer* renderer)
{
    //Menginisialisasi Paddle, Bola dan Score
    ThePlayers[0].init();
    ThePlayers[0].SetSide(Player::Side_Left);

    ThePlayers[1].init();
    ThePlayers[1].SetSide(Player::Side_Right);

    TheBall.init();

    Score[0] = 0;
    Score[1] = 0;

    debugPrinter = new DebugPrinter();
    debugPrinter->Init(renderer);

    return true;
}

bool Pong::Update()
{
    SDL_Init(SDL_INIT_AUDIO);
    SDL_Window* window = NULL;
    if (TheBall.IsOutOfBounds() == true)
    {
        Player::Side serveTo = Player::Side_Undefined;
        if (TheBall.OutOfBoundsSide() == Player::Side_Left) // Jika Bola mengenai sisi kiri
        {
            SDL_LoadWAV("Sound/Chicken.wav", &wavSpec, &wavBuffer, &wavLength);
            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
            int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
            SDL_PauseAudioDevice(deviceId, 0);


            Score[1]++;// Menambah nilai sebeblah kanan
            serveTo = Player::Side_Left;
            if (Score[1] == 8) {
                SDL_LoadWAV("Sound/PlayerTwo.wav", &wavSpec, &wavBuffer, &wavLength);
                SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
                int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                SDL_PauseAudioDevice(deviceId, 0);
                SDL_Delay(4000);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }

        }

        if (TheBall.OutOfBoundsSide() == Player::Side_Right)
        {
            SDL_LoadWAV("Sound/Duck.wav", &wavSpec, &wavBuffer, &wavLength);
            SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
            int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
            SDL_PauseAudioDevice(deviceId, 0);

            Score[0]++; // Menambah nilai sebelah Kiri
            serveTo = Player::Side_Right;
            if (Score[0] == 8) {
                SDL_LoadWAV("Sound/PlayerOne.wav", &wavSpec, &wavBuffer, &wavLength);
                SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
                int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                SDL_PauseAudioDevice(deviceId, 0);
                SDL_Delay(4000);
                SDL_DestroyWindow(window);
                SDL_Quit();
            }
        }

        TheBall.init();
        TheBall.ServeTo(serveTo);
    }
    else
    {
        if (((TheBall.IsColliding(ThePlayers[0]) == true) && (TheBall.IsGoingTo() == Player::Side_Left))
            || ((TheBall.IsColliding(ThePlayers[1]) == true) && (TheBall.IsGoingTo() == Player::Side_Right))
            )
        {
            TheBall.PlayerReturns();
        }

        ThePlayers[0].Move();
        ThePlayers[1].Move();
    }

    TheBall.Move();

    return true;
}

bool Pong::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = 800;
    rect.h = 600;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);//Mengatur Warna Papan
    SDL_RenderFillRect(renderer, &rect);

    DrawCourt(renderer);

    ThePlayers[0].Render(renderer);
    ThePlayers[1].Render(renderer);

    TheBall.Render(renderer);

    char str[255];
    sprintf(str, "%d - %d", Score[0], Score[1]);

    debugPrinter->SetScale(8, 8); //Mengatur Besar Score
    debugPrinter->SetJustification(DebugPrinter::Justifiy_Centre); // Mengatur letak Score
    debugPrinter->Print(renderer, 400, 20, RGBTOCOLOR(0, 0, 0), str); //Mengatur Warna Score
    debugPrinter->SetScale(0.001, 1);
    debugPrinter->SetJustification(DebugPrinter::Justifiy_Left);


    return true;
}

bool Pong::Shutdown()
{
    return true;
}



void Pong::DrawCourt(SDL_Renderer* renderer) //Mengatur Garis Papan
{
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 100;
    rect.w = 800;
    rect.h = 10;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect.x = 0;
    rect.y = 590;
    rect.w = 800;
    rect.h = 10;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect.x = 395;
    rect.y = 100;
    rect.w = 10;
    rect.h = 600;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

}