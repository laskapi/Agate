/*
  ==============================================================================

    CStepsCountSelector.h
    Created: 5 May 2024 11:21:41pm
    Author:  Piotrek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CStepsCountSelector  : public juce::Component
{
public:
    CStepsCountSelector(GateModel &model)
    {
        plusBtt.setButtonText("+");
        plusBtt.onClick = [&] {model.addStep(); };

        minusBtt.setButtonText("-");
        minusBtt.onClick = [&] {model.removeStep(); };

        addAndMakeVisible(plusBtt);
        addAndMakeVisible(minusBtt);
    }

    ~CStepsCountSelector() override
    {
    }

    void paint (juce::Graphics& g) override
    {
    
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //    g.setColour (juce::Colours::white);
    //    g.setFont (14.0f);
    //    g.drawText ("CStepsCountSelector", getLocalBounds(),
    //                juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        auto area = getLocalBounds();

        plusBtt.setBounds(area.removeFromTop(area.getHeight()>>1).reduced(5));
        minusBtt.setBounds(area.reduced(5));
    }

private:
    TextButton plusBtt;
    TextButton minusBtt;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CStepsCountSelector)
};
