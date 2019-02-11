// file:	Events\EventArgs.h
//
// summary:	Base definition for an EventArgs class

#pragma once

namespace IlluminiaStudios::HandyCPP {

    /// <summary>
    /// The base class for all event args
    /// </summary>
    class EventArgs {

    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        EventArgs();

        /// <summary>
        /// Move constructor.
        /// </summary>
        ///
        /// <param name="other">[in,out] The other.</param>
        EventArgs(EventArgs&& other);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~EventArgs();

        /// <summary>
        /// Instance of an empty event args
        /// </summary>
        static EventArgs Empty;

        /// <summary>
        /// Move assignment operator.
        /// </summary>
        ///
        /// <param name="other">[in,out] The other.</param>
        ///
        /// <returns>
        /// A shallow copy of this object.
        /// </returns>
        virtual EventArgs& operator=(EventArgs&& other);
    };
}
