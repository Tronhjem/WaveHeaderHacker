#include "MainComponent.h"
#include <iostream>




//==============================================================================
MainComponent::MainComponent()
{
    setSize (windowWidth, windowHeigth);
    
    randomPoints = new Vector2[100];
    Random r(time(nullptr));
    for (int i = 0; i < 100; ++i)
    {
        int ranX = r.nextInt(windowWidth);
        int ranY = r.nextInt(windowWidth);
        randomPoints[i] = Vector2(ranX, ranY);
    }
    LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
    
    loadButton.setBounds(75, 210, 150, 25);
    addAndMakeVisible(&loadButton);
    loadButton.addListener(this);
    
    
    saveButton.setBounds(75, 250, 150, 25);
    addAndMakeVisible(&saveButton);
    saveButton.addListener(this);
    
    addAndMakeVisible(&SampleRateField.Label);
    addAndMakeVisible(&SampleRateField.Editor);

    addAndMakeVisible(&ChannelsField.Label);
    addAndMakeVisible(&ChannelsField.Editor);

    addAndMakeVisible(&BitDepthField.Label);
    addAndMakeVisible(&BitDepthField.Editor);
 
}

void MainComponent::UpdateInfo()
{
    String s = std::to_string(waveReader.Info.SampleRate);
    SampleRateField.Editor.setText(s);
    
    s = std::to_string(waveReader.Info.Channels);
    ChannelsField.Editor.setText(s);
    
    s = std::to_string(waveReader.Info.BitsPerSample);
    BitDepthField.Editor.setText(s);
    
    Random r(time(nullptr));
    for (int i = 0; i < 100; ++i)
    {
        int ranX = r.nextInt(windowWidth);
        int ranY = r.nextInt(windowWidth);
        randomPoints[i] = Vector2(ranX, ranY);
    }
}


void MainComponent::buttonClicked(Button* b)
{
    if (b == &loadButton)
    {
        auto chooserFlags = juce::FileBrowserComponent::openMode
                          | juce::FileBrowserComponent::canSelectFiles;
        
        
        fileChooser.launchAsync (chooserFlags, [this] (const FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != File{})
            {
                waveFilePath = file.getFullPathName();
                if(!waveFilePath.endsWith(".wav"))
                {
                    DialogWindow window{"WARNING", Colour(80, 80, 80), true};
                    warningLabel.setBounds(30, 10, 200, 50);
                    warningLabel.setText("Only supports '.wav' files.\nNothing was loaded", NotificationType::dontSendNotification);
                    window.showDialog("Error", &warningLabel, this, Colour(0,0,0), true);
                    return;
                }
                    
                waveReader.ReadFile(waveFilePath.toStdString());
                UpdateInfo();
            }
        });
    }
    
    else if (b == &saveButton)
    {
        int newSampleRate = stoi(SampleRateField.Editor.getText().toStdString());
        waveReader.ChangeSampleRate(newSampleRate);
        
        int newChannel = stoi(ChannelsField.Editor.getText().toStdString());
        waveReader.ChangeChannels(newChannel);
        
        int newBithDepth = stoi(BitDepthField.Editor.getText().toStdString());
        waveReader.ChangeBitDepth(newBithDepth);
        
        String appendName = "_" + SampleRateField.Editor.getText() + "_" +
                            ChannelsField.Editor.getText() + "_" +
                            BitDepthField.Editor.getText();
        waveReader.WriteFile(appendName.toStdString());
    }
}

void MainComponent::choose(const FileChooser& a)
{
    
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (Colour(0, 0, 0));
    for (int i = 0; i < 100; ++i)
    {
        g.setColour(Colour(50, 30, 80));
        
        int x = randomPoints[i].x;
        int y = randomPoints[i].y;
        int x2 = randomPoints[i+1].y;
        int y2 = randomPoints[i+1].y;
        g.drawLine(x, y, x2, y2, 1);
    }
}

void MainComponent::resized()
{
}
