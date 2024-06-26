/*
  ==============================================================================

	GateContainer.cpp
	Created: 6 Apr 2024 6:32:36pm
	Author:  Piotrek

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CStepsContainer.h"


//==============================================================================


CStepsContainer::CStepsContainer(GateModel &model):model(model)
{
	model.addActionListener(this);

	for (int i = 0; i < model.size(); i++) {
		csteps.add(new CStep(model.getValue(i),model.getResolution(), String(i), *this));
		addAndMakeVisible(csteps[i]);
	}

}

CStepsContainer::~CStepsContainer()
{
	model.removeActionListener(this);
}

void CStepsContainer::paint(juce::Graphics& g)
{
	
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(juce::Colours::white);
	g.setFont(14.0f);
	g.drawText("GateContainer", getLocalBounds(),
		juce::Justification::top, true);
}

void CStepsContainer::resized()
{
	Rectangle bounds = getLocalBounds();
	int width = bounds.getWidth() / std::max(csteps.size(), 1);
	for (auto s : csteps) {
		s->setBounds(bounds.removeFromLeft(width).reduced(10, 10));
	}
}

void CStepsContainer::sliderValueChanged(juce::Slider* slider)
{
	model.setValue(slider->getComponentID().getIntValue(), slider->getValue());
}
//void CStepsContainer::buttonClicked(Button* button) {
//	model.setState(button->getComponentID().getLargeIntValue(), button->getToggleState());
//	}


void CStepsContainer::actionListenerCallback(const String& message)
{
	if (message.equalsIgnoreCase(GateModel::MSG_RES)) {
		for (auto step : csteps) {
			step->setResolution(model.getResolution());
		}
		return;
	}

	auto pos = csteps.size();
	if (message.equalsIgnoreCase(GateModel::MSG_ADD)) {
		
		csteps.add(new CStep(model.getValue(pos),model.getResolution(), String(pos), *this));
		addAndMakeVisible(csteps.getLast());
		resized();
	}
	else if (message.equalsIgnoreCase(GateModel::MSG_REMOVE)) {
		csteps.removeLast(1, true);
		resized();


	}
	
}
