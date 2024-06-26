/*
  ==============================================================================

    GateContainer.h
    Created: 6 Apr 2024 6:32:36pm
    Author:  Piotrek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "CStep.h"
#include "GateModel.h"

//==============================================================================
/*
*/
class CStepsContainer  : public juce::Component,public Slider::Listener,public::ActionListener
{
public:
    CStepsContainer(GateModel& model);
    ~CStepsContainer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider*) override;
    void actionListenerCallback(const String& message) override;
private:
    OwnedArray<CStep> csteps;
    GateModel& model;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CStepsContainer)
};
