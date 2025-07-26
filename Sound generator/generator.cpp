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
