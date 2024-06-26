/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
AgateAudioProcessorEditor::AgateAudioProcessorEditor(AgateAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), model(p.getModel()),
    cStepsContainer(model), cStepsCountSelector(model),
    cStepsResolutionSelector(model)//([this](int res) {model.setResolution(res); })

{

    DBG("create Plugin Editor");
    setSize (600, 300);
    addAndMakeVisible(cStepsCountSelector);    
    addAndMakeVisible(cStepsResolutionSelector);
    addAndMakeVisible(cStepsContainer);
 
}

AgateAudioProcessorEditor::~AgateAudioProcessorEditor()
{
    DBG("Delete PluginEditor");

}

//==============================================================================
void AgateAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Agate 1.0", getLocalBounds(), juce::Justification::centred, 1);
}

void AgateAudioProcessorEditor::resized()
{

    auto area = getLocalBounds();
    auto selectorsArea = area.removeFromLeft(getWidth() >> 3); 
    
   
    cStepsCountSelector.setBounds(selectorsArea.removeFromTop(getHeight() >> 1).reduced(5));
    cStepsResolutionSelector.setBounds(selectorsArea.reduced(5));
    cStepsContainer.setBounds(area.reduced(5));
    
}

