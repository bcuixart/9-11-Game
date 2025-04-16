#include "AudioEngine.hh"
#include "stb_vorbis.c"

AudioEngine::AudioEngine() : device(nullptr), context(nullptr)
{

}

void AudioEngine::DeleteAudioEngine() 
{
    for (auto& [_, clip] : audioClips)
        alDeleteBuffers(1, &clip.buffer);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void AudioEngine::Update(const ALfloat* position, const ALfloat* forward)
{
    SetListenerPosition(position, forward);
    CleanUpSources();
}

void AudioEngine::SetListenerPosition(const ALfloat* position, const ALfloat* forward) 
{
    alListener3f(AL_POSITION, position[0], position[1], position[2]);

    // OpenAL expects an array of 6 floats: forward then up
    ALfloat orientation[6] = {
        forward[0], forward[1], forward[2],
        0,      1,      0
    };

    alListenerfv(AL_ORIENTATION, orientation);
}

void AudioEngine::CleanUpSources() 
{
    auto it = activeSources.begin();
    while (it != activeSources.end()) {
        ALint state;
        alGetSourcei(*it, AL_SOURCE_STATE, &state);

        if (state == AL_STOPPED) {
            alDeleteSources(1, &(*it));
            it = activeSources.erase(it);
        }
        else {
            ++it;
        }
    }
}

ALuint AudioEngine::PlayAudio(const string& audioName, bool loop)
{
    auto it = audioClips.find(audioName);
    if (it == audioClips.end()) {
        AudioClip clip = LoadOGG(audioName.c_str());
        it = audioClips.insert({ audioName, clip }).first;
    }

    const AudioClip& clip = it->second;

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
    alSourcei(source, AL_BUFFER, clip.buffer);
    alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

    alSourcePlay(source);

    activeSources.push_back(source);

    return source;
}

ALuint AudioEngine::PlayAudio3D(const string& audioName, const ALfloat* position, bool loop)
{
    auto it = audioClips.find(audioName);
    if (it == audioClips.end()) {
        AudioClip clip = LoadOGG(audioName.c_str());
        it = audioClips.insert({ audioName, clip }).first;
    }

    const AudioClip& clip = it->second;

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, clip.buffer);
    alSourcef(source, AL_GAIN, 2.0f);
    alSourcef(source, AL_PITCH, 1.0f);

    alSource3f(source, AL_POSITION, position[0], position[1], position[2]);
    alSourcei(source, AL_SOURCE_RELATIVE, AL_FALSE); // It's in world space
    alSourcef(source, AL_ROLLOFF_FACTOR, 0.2f);       // Controls how volume decreases with distance
    alSourcef(source, AL_REFERENCE_DISTANCE, 2.0f);   // Distance where it starts to roll off
    alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

    alSourcePlay(source);

    activeSources.push_back(source);

    return source;
}

AudioEngine::AudioClip AudioEngine::LoadOGG(const char* filename)
{
    short* output;
    int channels, sampleRate;
    int samples = stb_vorbis_decode_filename(filename, &channels, &sampleRate, &output);

    if (samples < 0) {
        cout << "Failed to load OGG file" << endl;
    }

    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, output, samples * sizeof(short) * channels, sampleRate);

    free(output);

    return { buffer, format, sampleRate };
}

void AudioEngine::SetAudioSpeed(ALuint source, float speed) 
{
    alSourcef(source, AL_PITCH, speed);
}

bool AudioEngine::InitializeAudioEngine()
{
    device = alcOpenDevice(nullptr);
    if (!device) { 
        cout << "Failed to open audio device" << endl;
        return false;
    }

    context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    return true;
}
