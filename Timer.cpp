#include "Timer.h"

void Timer::Start() //Fungsi untuk start Counter waktu
{
    QueryPerformanceCounter(&start);
}

void Timer::Stop() //Fungsi untuk stop Counter waktu
{
    QueryPerformanceCounter(&stop);

    LastTime.QuadPart = stop.QuadPart - start.QuadPart;
}

float Timer::GetTime() //Fungsi untuk mendapat Counter waktu
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

    return (float)(LastTime.QuadPart / (float)freq.QuadPart);
}

float Timer::GetmS() //Fungsi untuk mendapat waktu dalam MilliSecond
{
    return GetTime() * 1000.0f;
}