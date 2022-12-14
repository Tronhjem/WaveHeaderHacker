#pragma once

#include <JuceHeader.h>
#include "WaveReader.hpp"
#include <cmath>

using namespace juce;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class HackerLookAndFeel : public juce::LookAndFeel_V4
{
public:
    HackerLookAndFeel()
    {
        setDefaultSansSerifTypefaceName("Roboto");
        setColour (TextButton::ColourIds::buttonColourId, Colour(0,0,0));
        setColour (TextEditor::backgroundColourId, Colour(0,0,0));
    }
};

class FieldComponent : public juce::Component
{
public:
    FieldComponent(int x, int y, String name): ComponentName(name)
    {
        Label.setBounds(x-4, y, width, labelHeight);
        Label.setText(ComponentName, NotificationType::dontSendNotification);
        
        Editor.setBounds (x, y + labelHeight, width, editorHeight);
        Editor.setInputRestrictions(restrictionLength, numberRestriction);
        Font f;
        f.setSizeAndStyle(400.f, "Roboto", 10.f, 10.f);
        Editor.setFont(f);
    };
    
    ~FieldComponent()
    {
        
    };
    
    void Add()
    {
        addAndMakeVisible(&Label);
        addAndMakeVisible(&Editor);
    }
    
    const String ComponentName;
    Label Label;
    TextEditor Editor {"EditorNAme:@"};
    
private:
    const int restrictionLength = 15;
    const String numberRestriction = "0123456789";
    const int labelHeight = 25;
    const int editorHeight = 25;
    const int width = 150;
    Font font {};
};

class Vector2
{
public:
    Vector2(int x, int y) : x(x), y(y) {};
    Vector2(){};
    int x;
    int y;
    float magnitude()
    {
        return sqrt((x*x)+(y*y));
    }
};





class MainComponent  :  public juce::Component,
                        public juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    void UpdateInfo();
    void buttonClicked(Button*) override;
    void choose(const FileChooser &);
    
    HackerLookAndFeel lookAndFeel;
    FieldComponent ChannelsField    {75, 10, "Channels"};
    
    FieldComponent SampleRateField  {75, 70, "Sample Rate"};
    FieldComponent BitDepthField    {75, 130, "Bit Depth"};
    
    TextButton loadButton {"Load Wave"};
    TextButton saveButton {"Save New File"};
    FileChooser fileChooser {"title"};
    
    int windowWidth = 300;
    int windowHeigth = 300;
    String waveFilePath;
    Vector2* randomPoints;
    
    Font font {};
    Label warningLabel {"Only supports .wav files"};
    
    WaveFileReader waveReader {};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
