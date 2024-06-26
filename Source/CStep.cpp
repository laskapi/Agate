/*
  ==============================================================================

	CStep.cpp
	Created: 10 Apr 2024 5:27:31pm
	Author:  Piotrek

  ==============================================================================
*/

//#include <JuceHeader.h>
#include "CStep.h"

//==============================================================================
CStep::CStep(double val,int resolution,String id, Slider::Listener& listener)
{
	
	setSliderStyle(juce::Slider::LinearBarVertical);
	setRange(0.0, 1.0, 1.0/resolution);
	setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	setValue(val);
	setComponentID(id);
	setLookAndFeel(&mLaf);
		
	addListener(&listener);
	
	//step.setToggleState((int)val, false);

	//addAndMakeVisible(step);


}

CStep::~CStep()
{
	setLookAndFeel(nullptr);
	

}

void CStep::paint(juce::Graphics& g)
{
	Slider::paint(g); 
	//g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(juce::Colours::white);
	g.setFont(14.0f);

	int val = getValue() * 100;
	//double whole;
	//double fraction = std::modf(val, &whole);
	DBG("val"<<val);
	int v = val;
	g.drawText(std::to_string(v), getLocalBounds(),
	juce::Justification::centred, true);   
	
}

//void CStep::resized()
//{
//
//	auto area = getLocalBounds();
//	setBounds(area);
//	
//}

void CStep::setResolution(int res)
{
	double oldVal = getValue();
	double interval = 1.0 / res;
	int val = round(oldVal / interval);
	
	setRange(0.0,1.0, interval);
	setValue(val* interval);
	repaint();
}
