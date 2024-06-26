/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CStepsContainer.h"
#include "CStepsCountSelector.h"
#include "CStepsResolutionSelector.h"
//==============================================================================
/**
*/
class AgateAudioProcessorEditor  : public juce::AudioProcessorEditor
                                   
{
public:
    AgateAudioProcessorEditor (AgateAudioProcessor&);
    ~AgateAudioProcessorEditor() override;

    //==============================================================================
   
    void paint (juce::Graphics&) override;
    void resized() override;
  
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AgateAudioProcessor& audioProcessor;
    GateModel& model;
    CStepsContainer cStepsContainer;
    CStepsCountSelector cStepsCountSelector;
    CStepsResolutionSelector cStepsResolutionSelector;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AgateAudioProcessorEditor)
};
