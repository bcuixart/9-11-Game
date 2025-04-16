#ifndef AUDIOENGINE_HH
#define AUDIOENGINE_HH

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <AL/al.h>
#include <AL/alc.h>

using namespace std;

class AudioEngine {
public:
	AudioEngine();

	void DeleteAudioEngine();

	bool InitializeAudioEngine();

	ALuint PlayAudio(const string& audioName, bool loop);
	ALuint PlayAudio3D(const string& audioName, const ALfloat* position, bool loop);

	void SetAudioSpeed(ALuint source, float speed);

	void Update(const ALfloat* position, const ALfloat* forward);

private:

	void CleanUpSources();
	void SetListenerPosition(const ALfloat* position, const ALfloat* forward);

	ALCdevice* device;
	ALCcontext* context;

	struct AudioClip {
		ALuint buffer;
		ALenum format;
		ALsizei sampleRate;
	};

	AudioClip LoadOGG(const char* filename);

	map<string, AudioClip> audioClips;
	vector<ALuint> activeSources;
};

#endif