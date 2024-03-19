#include "EngineTime.h"

// This code is from Blat Blatnik, thank you Blat VERY COOL
// Check him out over here: https://blog.bearcats.nl/perfect-sleep-function/
void EngineTime::Sleep(double seconds)
{
    auto t = std::chrono::high_resolution_clock::now();
    auto target = t + std::chrono::nanoseconds(int64_t(seconds * 1e9));

    static HANDLE timer;
    if (!timer)
        timer = CreateWaitableTimerExW(NULL, NULL,
                                       CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
                                       TIMER_ALL_ACCESS);

    int64_t maxTicks = PERIOD * 9'500;
    for (;;) {
        int64_t remaining = (target - t).count();
        int64_t ticks = (remaining - TOLERANCE) / 100;
        if (ticks <= 0)
            break;
        if (ticks > maxTicks)
            ticks = maxTicks;

        LARGE_INTEGER due;
        due.QuadPart = -ticks;
        SetWaitableTimerEx(timer, &due, 0, NULL, NULL, NULL, 0);
        WaitForSingleObject(timer, INFINITE);
        t = std::chrono::high_resolution_clock::now();
    }

    // spin
    while (std::chrono::high_resolution_clock::now() < target)
        YieldProcessor();
}

void EngineTime::UpdateStartTime()
{
    startTime = std::chrono::system_clock::now();
}

void EngineTime::UpdateEndTime(const int& fps)
{
    // calculate time it took for engine to excecute
    endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    // Throttle the gameEngine if the engine has more fps than the target FrameRate
    double targetFrameRate = 1.0 / (double)fps; // TODO: Add Framerate
    if (elapsedTime.count() < targetFrameRate)
        Sleep(targetFrameRate - elapsedTime.count());

    // Calculate deltaTime and other
    endTime = std::chrono::system_clock::now();
    elapsedTime = endTime - startTime;
    deltaTime = elapsedTime.count();
    milliSeconds = elapsedTime.count() * 1000;
}

std::string EngineTime::time_in_HH_MM_SS_MMM()
{
    /*
     * using namespace std::chrono;
     * // get current time
     * auto now = system_clock::now();
     * // get number of milliseconds for the current second
     * // (remainder after division into seconds)
     * auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
     * // convert to std::time_t in order to convert to std::tm (broken time)
     * auto timer = system_clock::to_time_t(now);
     * // convert to broken time
     * std::tm bt = *std::localtime(&timer);
     * std::ostringstream oss;
     * oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
     * oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
     * return oss.str();
     */
    using namespace std::chrono;
    auto now = system_clock::now();
    auto timer = system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);
    std::ostringstream oss; //TODO remove stream
    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    return oss.str();
}