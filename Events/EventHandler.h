// file:	Events\EventHandler.h
//
// summary:	Template definition for and EventHandler
#pragma once

#include "EventHandlerBase.h"

namespace IlluminiaStudios::HandyCPP {

    /// <summary>
    /// Event Handler class definition.
    /// This class implements the observer pattern to
    /// implement the event handling and firing mechanism
    /// </summary>
    /// 
    /// <typeparam name="T">Creating class</typeparam>
    template<class T, class E>
    class EventHandler : public EventHandlerBase<EventHandler<T, E>, E> {

        /// <summary>
        /// Reference to the friend class that created the EventHandler.
        /// Only this class can call Invoke
        /// </summary>
        friend T;

    protected: //Protected Methods

        /// <summary>
        /// Invoke all the subscribers.
        /// </summary>
        /// <remarks>
        /// This operation uses a lock guard on the internal subscribers set
        /// </remarks>
        /// <param name="_sender">[in,out] Reference of the send of the event</param>
        /// <param name="_args">[in,out] The arguments.</param>
        void Invoke(const void* _sender, E& _args) override;

    };

    //Template Definition
    
    template<class T, class E>
    void EventHandler<T, E>::Invoke(const void * _sender, E& _args) {
        EventHandlerBase<EventHandler<T, E>, E>::Invoke(_sender, _args);
    }
}
