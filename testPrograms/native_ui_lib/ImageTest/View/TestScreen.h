/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/**
 * @file TestScreen.h
 * @author Bogdan Iusco.
 *
 * @brief Shows the tested Image widget.
 */

#ifndef IMAGE_TEST_TEST_SCREEN_H_
#define IMAGE_TEST_TEST_SCREEN_H_

#include <maapi.h>

#include <MAUtil/util.h>

// Include all the wrappers.
#include <NativeUI/Widgets.h>

using namespace NativeUI;

namespace ImageTest
{
	/**
	 * Class that creates a screen that displays all the contacts.
	 */
	class TestScreen:
		public Screen,
		public WidgetEventListener,
		public ButtonListener,
		public SliderListener
	{

	public:
		/**
		 * Constructor.
		 */
		TestScreen();

		/**
		 * Destructor.
		 */
		virtual ~TestScreen();

		/**
		 * Display a image from a given file path.
		 * @param path Image file path.
		 */
		void showImageUsingFilePath(const MAUtil::String& path);

		/**
		 * Display the image from resources.
		 * @param handle Image handle.
		 */
		void showImageUsingHandle(MAHandle handle);

		/**
		 * Get previous set image path.
		 */
		MAUtil::String getImagePath();

	private:

		/**
		 * This method is called when there is an event for this widget.
		 * @param widget The widget object of the event.
		 * @param widgetEventData The low-level event data.
		 */
		virtual void handleWidgetEvent(
			Widget* widget,
			MAWidgetEventData* widgetEventData);

		/**
		 * Creates and adds main layout to the screen.
		 */
		void createMainLayout();

		/**
		 * This method is called when the value of the slider was modified by
		 * the user.
		 * @param slider The slider object that generated the event.
		 * @param sliderValue The new slider's value.
		 */
		virtual void sliderValueChanged(
			Slider* slider,
			const int sliderValue);

		/**
		 * This method is called if the touch-up event was inside the
		 * bounds of the button.
		 * @param button The button object that generated the event.
		 */
		virtual void buttonClicked(Widget* button);
	private:
		/**
		 * Main layout.
		 */
		VerticalLayout* mMainLayout;

		Image* mImage;

		Button* mGetImageAlpha;
		Label* mImageAlpha;
		Slider* mImageSlider;
		VerticalLayout* mLayout;
		Button* mGetLayoutAlpha;
		Label* mLayoutAlpha;
		Slider* mLayoutSlider;
	};

} // end of ImageTest

#endif /* IMAGE_TEST_TEST_SCREEN_H_ */
