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


int audio_callback(const void* inputBuffer, void* outputBuffer,
    unsigned long frames_per_buffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    WaveData* data = static_cast<WaveData*>(userData);
    float* out = static_cast<float*>(outputBuffer);
    (void)inputBuffer; // Unused variable

    for (unsigned long i = 0; i < frames_per_buffer; i++) {
        if (data->position < data->samples.size()) {
            out[i] = data->samples[data->position++];
        } else {
            out[i] = 0.0f;
        }
    }

    return paContinue;
}


int main() {
    float carrierFreq, modulatorFreq, duration;

    std::cout << "Enter carrier frequency (Hz): ";
    std::cin >> carrierFreq;

    std::cout << "Enter frequency of the modulating wave (Hz): ";
    std::cin >> modulatorFreq;

    std::cout << "Enter wave signal duration (sec): ";
    std::cin >> duration;

    WaveData waveData;
    generate_sound(carrierFreq, modulatorFreq, duration, waveData);

    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "ERROR (portaudio): " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    PaStream* stream;
    err = Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audio_callback, &waveData);
    if (err != paNoError) {
        std::cerr << "ERROR (portaudio): " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "ERROR (portaudio): " << Pa_GetErrorText(err) << std::endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    Pa_Sleep(duration * 1000);

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "ERROR (portaudio): " << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "ERROR (portaudio): " << Pa_GetErrorText(err) << std::endl;
    }

    Pa_Terminate();

    return 0;
}

