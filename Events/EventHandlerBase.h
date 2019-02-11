// file:	Events\EventHandlerBase.h
//
// summary:	Declares the event handler base class

#pragma once

#include "EventArgs.h"

#include <functional>
#include <unordered_map>
#include <mutex>

namespace IlluminiaStudios::HandyCPP {

    /// <summary>
    /// Defines an alias representing the event subscriber signature.
    /// </summary>
    typedef std::function<void(const void*, EventArgs&)> EventSubscriber;

    /// <summary>
    /// Event Handler class definition.
    /// This class implements the observer pattern to
    /// implement the event handling and firing mechanism
    /// </summary>
    ///
    /// <typeparam name="T">The Derived Class.</typeparam>
    template<class T>
    class EventHandlerBase {

    protected:
        EventHandlerBase() {}

    public:
        virtual ~EventHandlerBase() {}

        /// <summary>
        /// Add a subscriber to the event handler.
        /// </summary>
        ///
        /// <param name="_subscriber">The subscriber to add.</param>
        ///
        /// <returns>
        /// Returns a reference to this EventHandler.
        /// </returns>
        T& operator+= (const EventSubscriber& _subscriber);

        /// <summary>
        /// Add a subscriber to the event handler.
        /// </summary>
        ///
        /// <param name="_subscriber">The subscriber to remove.</param>
        ///
        /// <returns>
        /// Returns a reference to this EventHandler.
        /// </returns>
        T& operator-= (const EventSubscriber& _subscriber);

    protected: // Protected Methods

        /// <summary>
        /// Invoke all the subscribers.
        /// </summary>
        /// <remarks>
        /// This operation uses a lock guard on the internal subscribers set
        /// </remarks>
        /// <param name="_sender">[in,out] Reference of the send of the event</param>
        /// <param name="_args">[in,out] The arguments.</param>
        virtual void Invoke(const void* _sender, EventArgs& _args);

    private: // Private Members

        /// <summary>
        /// The collection of subscribers.
        /// </summary>
        std::unordered_map<const EventSubscriber*, EventSubscriber> subscribers;

        /// <summary>
        /// The subscribers mutex.
        /// </summary>
        std::mutex subscribersMutex;

    };

    //Template Definition

    template<class T>
    T& EventHandlerBase<T>::operator+=(const EventSubscriber& _subscriber) {

        std::lock_guard<std::mutex> lock(subscribersMutex);
        subscribers[(&_subscriber)] = _subscriber;

        return static_cast<T&>(*this);
    }

    template<class T>
    T& EventHandlerBase<T>::operator-=(const EventSubscriber & _subscriber) {

        std::lock_guard<std::mutex> lock(subscribersMutex);
        subscribers.erase(&_subscriber);

        return  static_cast<T&>(*this);
    }

    template<class T>
    void EventHandlerBase<T>::Invoke(const void * _sender, EventArgs& _args) {

        std::lock_guard<std::mutex> lock(subscribersMutex);

        for (const auto& eventHander : subscribers) {
            std::invoke(eventHander.second, _sender, _args);
        }
    }
}
