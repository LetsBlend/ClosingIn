#pragma once

#define TOLERANCE 1'020'000
#define PERIOD 1

class EngineTime
{
public:
    //    inline static float timeScale = 1;
    // Average fps of the last 20 frames
    //    inline static int fps = 0;
    // Amount of time it took for one iteration in milliSeconds
    float milliSeconds = 0;
    // Amount of time it took for one iteration in seconds
    double deltaTime = 1;
    //    inline static double realTimeSinceStartUp = 0;
    //    inline static double timeSinceStartUp = 0;

    void Sleep(double seconds);

    void UpdateStartTime();
    void UpdateEndTime(const int& fps);

    static std::string time_in_HH_MM_SS_MMM();

private:
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
};