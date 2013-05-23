/*
Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file WidgetManager.h
 * @author Mikael Kindborg
 *
 * The WidgetManager manages widget events and dispatches
 * them to the target widgets.
 */

#include <mastring.h>           // C string functions

#include "WidgetManager.h"  // Header file for this class

namespace NativeUI
{

    /**
     * Initialize the singleton variable to NULL.
     */
    WidgetManager* WidgetManager::sInstance = NULL;

    /**
     * Constructor.
     */
    WidgetManager::WidgetManager()
    {
        // Add me as a custom event listener.
        MAUtil::Environment::getEnvironment().addCustomEventListener(this);
    }

    /**
     * Destructor.
     */
    WidgetManager::~WidgetManager()
    {
        // Remove me as a custom event listener.
        MAUtil::Environment::getEnvironment().removeCustomEventListener(this);
    }

    /**
     * Return the single instance of this class.
     */
    WidgetManager* WidgetManager::getInstance()
    {
        if (NULL == WidgetManager::sInstance)
        {
            WidgetManager::sInstance = new WidgetManager();
        }

        return sInstance;
    }

    /**
     * Destroy the single instance of this class.
     * Call this method only when the application will exit.
     */
    void WidgetManager::destroyInstance()
    {
        delete WidgetManager::sInstance;
    }

    /**
     * Implementation of CustomEventListener interface.
     * This method will get called whenever there is a
     * widget event generated by the system.
     * @param event The new received event.
     */
    void WidgetManager::customEvent(const MAEvent& event)
    {
        // Check if this is a widget event.
        if (EVENT_TYPE_WIDGET == event.type)
        {
            // Get the widget event data structure.
            MAWidgetEventData* eventData = (MAWidgetEventData*) event.data;

            // Check if the widget exists in the map.
            if (mWidgetMap.end() != mWidgetMap.find(eventData->widgetHandle))
            {
                // Get the widget object that wraps the widget handle.
                Widget* widget = mWidgetMap[eventData->widgetHandle];

                // Call the widget's event handling method.
                widget->handleWidgetEvent(eventData);
            }
        }
    }

    /**
     * Add a widget to the map that holds widgets.
     * The widget will receive custom events.
     * @param widgetHandle The handle of the widget that needs to be registered.
     * @param widget The widget that needs to be registered.
     * The ownership of the widget is not passed to this method.
     */
    void WidgetManager::registerWidget(MAHandle widgetHandle, Widget* widget)
    {
        checkNativeUISupport(widgetHandle);
        mWidgetMap[widgetHandle] = widget;
    }

    /**
     * Remove a widget from the map that holds widgets.
     * The widget will not receive custom events.
     * @param widgetHandle The handle of the widget that needs to be unregistered.
     */
    void WidgetManager::unregisterWidget(MAHandle widgetHandle)
    {
        mWidgetMap.erase(widgetHandle);
    }

    /**
     * Error handling for devices that do not support NativeUI.
     * Here we throw a panic if NativeUI is not supported.
     * @param result The widget handle.
     */
    void WidgetManager::checkNativeUISupport(MAHandle result) const
    {
        if (-1 == result)
        {
            maPanic(0,
                "This application uses Native UI, which is not supported "
                "on the current platform. Please select another target profile "
                "in the right-hand profile panel.");
        }
    }

} // namespace NativeUI
