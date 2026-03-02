#include "../../../includes/ui/graph/FrequencyGraph.hpp"

FrequencyGraph::FrequencyGraph(int sampleRate) {
    setOpaque(true);
    this->sampleRate = sampleRate;
}

FrequencyGraph::~FrequencyGraph() = default;

void FrequencyGraph::MyFFT(std::vector<std::complex<float>>& input) {
    int N = static_cast<int>(input.size());

    for (int step = 1; step < N; step *= 2)
    {
        int jump = step * 2;

        for (int group = 0; group < N; group += jump)
        {
            for (int k = 0; k < step; k++)
            {
                float angle = -2.0f * M_PI * k / jump;
                std::complex<float> twiddle = std::polar(1.0f, angle);

                std::complex<float> even = input[group + k];
                std::complex<float> odd  = input[group + k + step] * twiddle;

                this->fftTmpBuffer[group + k]        = even + odd;
                this->fftTmpBuffer[group + k + step] = even - odd;
            }
        }

        input = this->fftTmpBuffer;
    }
}

void FrequencyGraph::setBuffer(const juce::AudioBuffer<float>& buffer) {
    this->displayBuffer.makeCopyOf(buffer);

    int numSamples = buffer.getNumSamples();
    this->fftInputBuffer.resize(numSamples);
    this->fftTmpBuffer.resize(numSamples);
    this->xCoord.resize(numSamples);
    this->yCoord.resize(numSamples);

    const float* channelData = buffer.getReadPointer(0);
    for (int i = 0; i < numSamples; i++) {
        this->fftInputBuffer[i] = std::complex<float>(channelData[i], 0.0f);
    }

    repaint();
}

void FrequencyGraph::drawGraph(juce::Graphics& g) {
    g.setColour(juce::Colours::black);
    
    int width = getLocalBounds().getWidth();
	int height = getLocalBounds().getHeight();
    float minFreq = 18.0f;
    float maxFreq = 21000.0f;
    float mindB = -100.0f;
    float maxdB = 0.0f;
    std::size_t bufferSize = this->fftInputBuffer.size();

    this->MyFFT(this->fftInputBuffer);

    for (std::size_t i = 0; i < bufferSize / 2; i++) {
        auto freq = (i * this->sampleRate) / bufferSize;
        auto magnitude = std::abs(this->fftInputBuffer[i].real());
        auto db = 20.0f * log10(magnitude + 0.000001f);

        this->xCoord[i] = log10(freq / minFreq) / log10(maxFreq / minFreq);
        if (i == 0)
            this->yCoord[i] = 0.0f;
        else
            this->yCoord[i] = (db - mindB) / (maxdB - mindB);

        this->xCoord[i] = juce::jlimit(0.0f, 1.0f, this->xCoord[i]);
        this->yCoord[i] = juce::jlimit(0.0f, 1.0f, this->yCoord[i]);
    }

    float widthPerBox = width / (bufferSize / 2);

    for (size_t i = 1; i < bufferSize / 2; ++i) {
        g.drawRect({
            this->xCoord[i] * width, 
            0.0f,
            widthPerBox,
            height * (1.0f - this->yCoord[i]),
        }, 2.f);
        //g.drawLine(
        //    this->xCoord[i-1] * width, 
        //    1.0f, 
        //    this->xCoord[i] * width, 
        //    height * (1.0f - this->yCoord[i]));
    }

    //for (size_t i = 1; i < bufferSize / 2; ++i) {
    //    g.drawLine(
    //        this->xCoord[i-1] * width, 
    //        height * (1.0f - this->yCoord[i-1]), 
    //        this->xCoord[i] * width, 
    //        height * (1.0f - this->yCoord[i]));
    //}
}

