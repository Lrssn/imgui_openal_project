#pragma warning(disable: 4996)

#include <iostream>
#include <al.h>
#include <alc.h>
//#include <AL/alut.h>

static void list_audio_devices(const ALCchar *devices);


int main(int argc, char** argv) {
	
	//Get Audio devices
	
	ALCdevice *device;
	ALboolean enumeration;
	device = alcOpenDevice(NULL);

	if (!device) {
		std::cout << "OPENAL::ERROR : COULD NOT FIND DEVICES" << std::endl;
	}

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

	if (enumeration == AL_FALSE)
		std::cout << "OPENAL::ERROR : ENUMERATION NOT SUPPORTED" << std::endl;
	else
		list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	
	alGetError();
	//create a context for audio
	ALCcontext *context;

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
		std::cout << "OPENAL::ERROR : COULD NOT CREATE CONTEXT" << std::endl;
	
	ALCenum error;
	error = alGetError();
	if (error != AL_NO_ERROR)
		std::cout << "OPENAL::ERROR : ERROR AFTER CONTEXT CREATION" << std::endl;

	//create source
	ALuint source;
	alGenSources((ALuint)1, &source); // create 1 source object
	
	//Edit source parameters
	alSourcef(source, AL_PITCH, 1);
	// check for errors
	alSourcef(source, AL_GAIN, 1);
	// check for errors
	alSource3f(source, AL_POSITION, 0, 0, 0);
	// check for errors
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	// check for errors
	alSourcei(source, AL_LOOPING, AL_FALSE);
	// check for errros

	//create buffer
	ALuint buffer;

	alGenBuffers((ALuint)1, &buffer);//generate 1 buffer object

	//load audiostream to buffer
	ALsizei size, freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop = AL_FALSE;
	//ALbyte file = (ALbyte)("res\audio\imperial_march.wav");

	alutLoadWAVFile("res\audio\imperial_march.wav", &format, &data, &size, &freq, &loop);

	std::cout << "format = " << format << std::endl;
	std::cout << "data = " << data << std::endl;


	error = alGetError();
	if (error != AL_NO_ERROR)
		std::cout << "OPENAL::ERROR : CAN NOT LOAD FILE" << std::endl;

	//load wav file into buffer
	alBufferData(buffer, format, &data, size, freq);
	
	error = alGetError();
	if (error != AL_NO_ERROR)
		std::cout << "OPENAL::ERROR : CAN NOT LOAD FILE IN BUFFER" << std::endl;
	
	//bind source to buffer
	alSourcei(source, AL_BUFFER, buffer);

	error = alGetError();
	if (error != AL_NO_ERROR)
		std::cout << "OPENAL::ERROR : CAN NOT MERGE SOURCE AND BUFFER" << std::endl;


	//play source
	alSourcePlay(source);

	error = alGetError();
	if (error != AL_NO_ERROR)
		std::cout << "OPENAL::ERROR : CAN NOT PLAY FILE" << std::endl;
	
	ALint source_state;

	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	
	error = alGetError();
	if (error != AL_NO_ERROR)
		std::cout << "OPENAL::ERROR : CAN NOT GET SOURCE STATE" << std::endl;
	
	std::cout << source_state << std::endl;
	while (source_state == AL_PLAYING){
		std::cout << "entered" << std::endl;
		std::cout << source_state << std::endl;
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	}

	//cleanup
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

	system("pause");
	return 0;
}

static void list_audio_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}
