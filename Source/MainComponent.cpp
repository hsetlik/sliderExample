#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(freqSlider);
    freqSlider.setRange(50, 5000.0);
    freqSlider.setTextValueSuffix(" Hz");
    freqSlider.addListener(this);
    
    addAndMakeVisible(freqLabel);
    freqLabel.setText("Frequency", juce::dontSendNotification);
    freqLabel.attachToComponent(&freqSlider, true);
    
    addAndMakeVisible(durSlider);
    durSlider.setRange((1 / freqSlider.getMaximum()), (1/freqSlider.getMinimum()));
    durSlider.setTextValueSuffix(" s");
    durSlider.addListener(this);
    
    addAndMakeVisible(durLabel);
    durLabel.setText("Duration", juce::dontSendNotification);
    durLabel.attachToComponent(&durSlider, true);
    
    freqSlider.setValue(500.0);
    
    freqSlider.setSkewFactorFromMidPoint(500);
    durSlider.setSkewFactorFromMidPoint(0.002);
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto sliderLeft = 120;
    freqSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    durSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
}

void MainComponent::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &freqSlider){
        durSlider.setValue(1.0 / freqSlider.getValue(), juce::dontSendNotification);
    }
    else if (slider == &durSlider){
        freqSlider.setValue(1.0 / durSlider.getValue(), juce::dontSendNotification);
    }
}
