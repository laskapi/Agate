/*
  ==============================================================================

    StepComponent.h
    Created: 10 Apr 2024 5:27:31pm
    Author:  Piotrek

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string>
#include "Laf.h"

//==============================================================================
/*
*/
class CStep  : public juce::Slider
{
public:
    CStep(double val,int resolution,String id,Slider::Listener& listener);
    ~CStep() override;

    void paint (juce::Graphics&) override;
  //  void resized() override;
    void setResolution(int res);
private:
    Laf mLaf;
   // ToggleButton step;
 //   Slider step;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CStep)
};
