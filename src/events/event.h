/*
 * event.h
 *
 *  Created on: Aug 14, 2016
 *      Author: Eirik Skogstad
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <vector>

class Event {
public:
    Event() {}
    virtual ~Event() {}

    virtual std::string Type() = 0;
    virtual std::string Message() = 0;
};

class EventListener {
  public:
    virtual ~EventListener() {}
    virtual void HandleEvent(Event& event);
};

class EventBus {
  public:
    EventBus* Instance();
    void Register(EventListener& listener, std::string type);
    void SendEvent(Event& event);

  private:
    EventBus* instance_ = NULL;

    EventBus();

    // Declare copy constructors so that the compiler does not auto-generate
    EventBus(EventBus const& copy);
    EventBus& operator=(EventBus const& copy);

    std::vector<EventListener> subscribers_;
};

#endif /* EVENT_H_ */

