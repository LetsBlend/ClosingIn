//
// Created by Let'sBlend on 25/02/2024.
//

#ifndef CLOSINGIN_EVENT_H
#define CLOSINGIN_EVENT_H

#include "EventType.h"

struct EventContext
{
    //128 bits
    union
    {
        int64 i64[2];
        uint64 ui64[2];
        fint64 fi64[2];

        int32 i32[4];
        uint32 ui32[4];
        fint32 fi32[4];

        int16 i16[8];
        uint16 ui16[8];
        fint16 fi16[8];

        int8 i8[16];
        uint8 ui8[16];
        fint8 fi8[16];

        char c4[16];

        float f32[4];
        double d64[2];
    };
};

struct Listener
{
    Listener(const EventType& type, const std::function<void(Listener&)>& ptr)
    {
        eventType = type;
        listener = ptr;
    }
    ~Listener() = default;

    // The type of event listened to
    EventType eventType = EventType::None;
    // Pointer to the listener
    std::function<void(Listener&)> listener = nullptr;
    // Data that is different for different events, for example
    // MouseMoveEvent: mouse position, mousedelta..
    // KeyPressedEvent: Key..
    EventContext metaData{};

    bool operator==(const Listener& other) const
    {
        return eventType == other.eventType && &listener == &other.listener;
    }
};

template<>
struct std::hash<Listener>
{
    std::size_t operator()(const Listener& s) const noexcept
    {
        // Compute individual hash values for two members and combine them
        size_t h1 = std::hash<EventType>{}(s.eventType);
        auto ptr = reinterpret_cast<void*>(*(uintptr_t*)&s.listener);
        size_t h2 = std::hash<void*>{}(ptr);
        return h1 ^ (h2 << 1); // or use another method to combine hash values
    }
};

struct Sender
{
    // The type of event listened to
    EventType eventType;
    // Data that is different for different events, for example
    // MouseMoveEvent: mouse position, mousedelta..
    // KeyPressedEvent: Key..
    EventContext metaData{};
};

class Engine;

class Event
{
    friend class Engine;
public:
    // Registers a listener to a certain Event type
    template<typename T>
    static void RegisterEvent(EventType eventType, T* obj, void(T::*funcPtr)(Listener& listener))
    {
        listeners[(int)eventType].push_back(Listener{eventType, std::bind(funcPtr, obj, std::placeholders::_1)});
    }
    // Unregisters a listener to a certain Event type
    template<typename T>
    static void UnregisterEvent(EventType eventType, T* obj, void(T::*funcPtr)(Listener& listener))
    {
        std::vector<Listener>* data = &listeners[(int)eventType];
        auto it = std::find(data->begin(), data->end(), Listener{eventType, std::bind(funcPtr, obj, std::placeholders::_1)});
        if(it == data->end())
        {
            data->pop_back();
            return;
        }

        std::swap(*it, data->back());
        data->pop_back();
    }

    // Registers a listener to a certain Event type
    static void RegisterEvent(EventType eventType, const std::function<void(Listener&)>& funcPtr);
    // Unregisters a listener to a certain Event type
    static void UnregisterEvent(EventType eventType, const std::function<void(Listener&)>& funcPtr);

    // Push an event to be Fired
    static void PushEvent(const EventType& eventType);
    static void PushEvent(const EventType& eventType, const EventContext& e);

    static void FireEvents();

private:
    Event() = default;
    ~Event() = default;

    static void StartUp();
    static void ShutDown();

    // Stores all listeners&senders
    inline static std::vector<Listener> listeners[NUM_EVENTS];
    inline static std::array<Sender, NUM_EVENTS> senders;
};

#endif //CLOSINGIN_EVENT_H
