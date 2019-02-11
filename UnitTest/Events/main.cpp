// file:	main.cpp
//
// summary:	Implements the main class

#include "EventHandler.h"

#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <memory>

using namespace IlluminiaStudios::HandyCPP;

/// <summary>
/// Custom Event Args for Event Handler
/// </summary>
class CustomEventArgs : public EventArgs {
public:
    std::string PublicAccessors;
};

/// <summary>
/// Event Handler Unit Test class
/// </summary>
class UnitTest {

public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    UnitTest() {

        emptyEventHandler = SUBSCRIBE(&UnitTest::UnitTestEmptyArgsEventHandler);
        unitTestEmptyArgsEvent += emptyEventHandler;
        unitTestCustomArgsEvent += SUBSCRIBE(&UnitTest::UnitTestCusotmArgsEventHandler);
    }   

    /// <summary>
    /// Trigger the event with empty arguments.
    /// </summary>
    void TriggerEventWithEmptyArgs() {
        std::cout << "Invoke empty args events" << std::endl;
        unitTestEmptyArgsEvent.Invoke(this, EventArgs::Empty);
    }

    /// <summary>
    /// Trigger event with custom arguments.
    /// </summary>
    void TriggerEventWithCustomArgs() {

        std::cout << "Invoke custom args events" << std::endl;
        CustomEventArgs customArgs;
        customArgs.PublicAccessors = "Custom Test Event Arguments";

        // Args are passed by reference on the Invokers thread.
        // in a multi-threaded environment the handler,
        // the caller should always make a local copy of the Event Args
        // properties and operate on them in their own thread
        unitTestCustomArgsEvent.Invoke(this, customArgs);
    }  

    /// <summary>
    /// UnSubscribe empty arguments event.
    /// </summary>
    void UnSubscribeEmptyArgsEvent() {
        std::cout << "UnSubscribing empty args event handler" << std::endl;
        unitTestEmptyArgsEvent -= emptyEventHandler;
    }

private:
    /// <summary>
   /// Handler, called when the unit test event is fired
   /// </summary>
   ///
   /// <param name="_sender">The sender.</param>
   /// <param name="_args">[in,out] The arguments.</param>
    void UnitTestEmptyArgsEventHandler(const void * _sender, EventArgs & _args) {
        std::cout << "Event Handler" << std::endl;
    }

    /// <summary>
    /// Handler, called when the unit test event is fired
    /// </summary>
    ///
    /// <param name="_sender">The sender.</param>
    /// <param name="_args">[in,out] The arguments.</param>
    void UnitTestCusotmArgsEventHandler(const void * _sender, CustomEventArgs & _args) {
        std::cout << "Event Handler. Args : " << _args.PublicAccessors << std::endl;
    }


private:

    /// <summary>
    /// The unit test empty arguments event.
    /// </summary>
    EventHandler<UnitTest, EventArgs> unitTestEmptyArgsEvent;

    /// <summary>
    /// The unit test custom arguments event.
    /// </summary>
    EventHandler<UnitTest, CustomEventArgs> unitTestCustomArgsEvent;

    /// <summary>
    /// The reference to the eventHanlder, so we can unsubscribe later
    /// </summary>
    EmptyEventSubscriber emptyEventHandler;
};

/// <summary>
/// Main entry-point for this application.
/// </summary>
///
/// <param name="argc">The number of command-line arguments provided.</param>
/// <param name="argv">An array of command-line argument strings.</param>
///
/// <returns>
/// Exit-code for the process - 0 for success, else an error code.
/// </returns>
int main(int argc, char **argv) {

    UnitTest unitTest;

    unitTest.TriggerEventWithEmptyArgs();
    unitTest.TriggerEventWithCustomArgs();
    unitTest.UnSubscribeEmptyArgsEvent();
    unitTest.TriggerEventWithEmptyArgs(); //no events attached so output will be empty
    
    /*Ouput:
    Invoke empty args events
    Event Handler
    Invoke custom args events
    Event Handler. Args : Custom Test Event Arguments
    UnSubscribing empty args event handler
    Invoke empty args events */

    return 0;
}
