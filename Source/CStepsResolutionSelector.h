/*
  ==============================================================================

    CStepsResolutionSelector.h
    Created: 6 May 2024 12:02:31am
    Author:  Piotrek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include<functional>
//==============================================================================
/*
*/

using namespace std;
class CStepsResolutionSelector  : public juce::Component
{
public:
    CStepsResolutionSelector(GateModel& model) :model(model)
    {
        addAndMakeVisible(comboBox);
        for (int i = 1; i < 100; i++) {
        comboBox.addItem(to_string(i), i);
    }
        comboBox.setSelectedId(1);
        
        comboBox.onChange = [&] {model.setResolution(comboBox.getSelectedId()); };
        //setResolution.target<void()>();// [&] {setResolution(comboBox.getSelectedId()); };
        setSize(100, 100);
    }

    ~CStepsResolutionSelector() override
    {
    }
    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("CStepsResolutionSelector", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        comboBox.setBounds(getLocalBounds().reduced(5));
    }
    

private:
    ComboBox comboBox;
    GateModel& model;
    std::function<void(int)> callback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CStepsResolutionSelector)
};
