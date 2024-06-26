/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
AgateAudioProcessor::AgateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
}

AgateAudioProcessor::~AgateAudioProcessor()
{
}

//==============================================================================
const juce::String AgateAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool AgateAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool AgateAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool AgateAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double AgateAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int AgateAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int AgateAudioProcessor::getCurrentProgram()
{
	return 0;
}

void AgateAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String AgateAudioProcessor::getProgramName(int index)
{
	return {};
}

void AgateAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================


GateModel& AgateAudioProcessor::getModel() {
	return model;
}


void AgateAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	this->sampleRate = sampleRate;
	samples2modify = sampleRate / model.size();
}

void AgateAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AgateAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void AgateAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	
	juce::ScopedNoDenormals noDenormals;

	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());


	if (model.isEmpty()) {
		DBG("ret");
		return;
	}


	int freeBuffer = buffer.getNumSamples();
	int bufferWriteOffset = 0;
	long samples2modifyNow;

	
	if (samples2modify == 0) {

		lastStepVal = model.getValue(currentStep);
		currentTransitionTime = transitionTimeInSamples;
		currentStep = ++currentStep % model.size();
		samples2modify = sampleRate / model.size();
	}



	while (freeBuffer > 0) {
	
		if (currentTransitionTime > 0) {
			samples2modifyNow = std::min(currentTransitionTime, freeBuffer);
			buffer.applyGainRamp(bufferWriteOffset, samples2modifyNow, lastStepVal, model.getValue(currentStep));
			currentTransitionTime -= samples2modifyNow;
		}
				
		else{
			samples2modifyNow = std::min(samples2modify, (long)freeBuffer);
			buffer.applyGain(bufferWriteOffset, samples2modifyNow, model.getValue(currentStep));
		}

		samples2modify -= samples2modifyNow;
		bufferWriteOffset += samples2modifyNow;
		freeBuffer -= bufferWriteOffset;
		
	}
	
}

//==============================================================================
bool AgateAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AgateAudioProcessor::createEditor()
{
	return new AgateAudioProcessorEditor(*this);
}

//==============================================================================
void AgateAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void AgateAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new AgateAudioProcessor();
}
