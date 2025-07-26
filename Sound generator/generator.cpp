// Sound Generator for PC
// Enter:
// - carrier frequency (Hz)
// - modulation frequency (Hz)
// - sound signal duration (sec)

#include <iostream>
#include <cmath>
#include <vector>
#include <portaudio.h>
#define M_PI 3.14159265358979323846


const int SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 64;

struct WaveData {
    std::vector<float> samples;
    size_t position;
};


void generate_sound(float carrierFreq, float modulatorFreq, float duration, WaveData& waveData) {
    size_t numSamples = static_cast<size_t>(SAMPLE_RATE * duration);
    waveData.samples.resize(numSamples);
    waveData.position = 0;

    for (size_t i = 0; i < numSamples; i++) {
        float t = static_cast<float>(i) / SAMPLE_RATE;
        float carrierWave = 0.5f * sinf(2.0f * M_PI * carrierFreq * t);
        float modulatorWave = 0.5f * (1.0f + sinf(2.0f * M_PI * modulatorFreq * t));
        waveData.samples[i] = carrierWave * modulatorWave;
    }
}

