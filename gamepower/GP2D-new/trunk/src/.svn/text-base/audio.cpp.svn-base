#include "audio.h"
#include "core.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace gp {

GPAudioManager* GPAudioManager::m_instance = NULL;

/**
 * I'm using a constructor initialization list. Speed improvements and all
 * that, so I'd prefer if we start using this kind instead of assignment stuff.
 */
GPAudioManager::GPAudioManager() :
    m_isInit(false),
    m_frequency(44100),
    m_format(GP_AUDIO_S16),
    // m_channels(4),
    // XXX: This doesn't work with my config, so I had to lower it to 2.
    // XXX: In my config, I have stereo only, so I assume 4 channels would be
    // quadrafonic (sp?) so it wouldn't work. Maybe we should have it use the
    // maximum channels the computer can support? -DARKGuy
    m_channels(2),
    m_buffers(4096),
    m_mixingChannels(16) {
}

GPAudioManager::~GPAudioManager() {
    closeAudio();
}

GPAudioManager* GPAudioManager::getInstance() {
    if(m_instance == NULL) {
        m_instance = new GPAudioManager();
    }
    return m_instance;
}

void GPAudioManager::openAudio() throw (GPException) {
    // if already initialized, do not attempt to re-initialize.
    // user must deinit()
    if(m_isInit) {
        return;
    }

    if(Mix_OpenAudio(m_frequency, m_format, m_channels, m_buffers)) {
        stringstream ss;
        ss << "Failed to load initialize audio -> ";
        ss << "Rate: " << m_frequency << ", Format: " << m_format;
        ss << ", Channels: " << m_channels << ", Buffers: " << m_buffers;

        // save the error to use it in the throw, later.
        string s = Mix_GetError();
        // and clear it afterwards, because we will handle the error
        // in the try{}catch{} block surrounding this init() method
        // in usercode.
        SDL_ClearError();

        m_isInit = false;
        throw GPException(ss.str(), s);
    }




    // allocate the default amount of mixing channels
    setMixChannels(m_mixingChannels);

    m_isInit = true; // set initialized flag.
}

void GPAudioManager::closeAudio() {
    Mix_CloseAudio();
}

void GPAudioManager::setFormat(GPAudioFormat format) {
    m_format = format;
}

void GPAudioManager::setChannels(gpInt32 channels) {
    m_channels = channels;
}

void GPAudioManager::setChunkSize(gpInt32 chunkSize) {
    m_buffers = chunkSize;
}

void GPAudioManager::setFrequency(gpInt32 frequency) {
    m_frequency = frequency;
}

void GPAudioManager::setMixChannels(gpInt32 num) {
    m_mixingChannels = num;
    if(num >= 0) {
        Mix_AllocateChannels(num);
    }
}

void GPAudioManager::setMasterVolume(gpInt32 volume) {
    Mix_Volume(-1, volume);
    Mix_VolumeMusic(volume);
}

gpInt32 GPAudioManager::getMasterVolume() {
    return Mix_Volume(-1, -1);
}

gpInt32 GPAudioManager::getMixChannels() {
    // Mix_AllocateChannels(-1) can also be used to retrieve the channels.
    // Which is perhaps a better way, because this Mix_AllocateChannels can
    // also be used outside of GP. Values will then be inconsequent.
    return Mix_AllocateChannels(-1);
}

bool GPAudioManager::isInitialized() {
    return m_isInit;
}

//==============================================================================

GPAudioClip::GPAudioClip(string file) throw (GPException) :
    m_file(file) {
}

GPAudioClip::~GPAudioClip() {

}
const string& GPAudioClip::getFile() const {
    return m_file;
}

void GPAudioClip::setFile(const string& file) {
    m_file = file;
}

void GPAudioClip::setLoops(const gpInt32 loops) {
    m_loops = loops;
}

//==============================================================================

GPMusicClip::GPMusicClip(string file) throw (GPException) : GPAudioClip(file) {
    m_music = NULL; // set this stuff initially to null.
    try {
        init();
    } catch(GPException& ex) {
        throw; // rethrow it!
    }
}

GPMusicClip::~GPMusicClip() {
    if(m_music == NULL) {
        clog << "GP: Music was not loaded" << endl;
        return;
    }

    if(isPlaying()) {
        stop();
    }
    Mix_FreeMusic(m_music);
    m_music = NULL;
}

void GPMusicClip::init() throw (GPException) {
    if(m_music == NULL) {
        SDL_ClearError(); // clear any previous errors
        m_music = Mix_LoadMUS(m_file.c_str()); // then try to load the music.
        // if we still got a null, it means there have been errors.
        if(m_music == NULL) {
            string s = "Failed to load music file: `" + m_file + "'";
            // throw the exception to whatever this is calling (ctor anyone?)
            throw GPException(s, Mix_GetError());
        }
    }
}

void GPMusicClip::start() {
    if(!isPlaying()) {
        Mix_PlayMusic(m_music, -1);
    } else {
        cerr << "Cannot play two types of music simultaneously" << endl;
    }
}

void GPMusicClip::stop() {
    Mix_HaltMusic();
}

bool GPMusicClip::isPlaying() const {
    return Mix_PlayingMusic() == 1 ? true : false;
}

//==============================================================================

GPSoundClip::GPSoundClip(string file) throw (GPException) : GPAudioClip(file) {
    m_channel = -1;
    // m_chunk has to explicitly be set to null, or else it
    // has an undefined value of something which is not null.
    m_chunk = NULL;
    try {
        init();
    } catch(GPException& ex) {
        throw ex;
    }
}

GPSoundClip::~GPSoundClip() {
    // only free the chunk if it is not null.
    if(m_chunk != NULL) {
        Mix_FreeChunk(m_chunk);
    }
    m_chunk = NULL;
}

void GPSoundClip::init() throw (GPException) {
    if(m_chunk == NULL) {
        SDL_ClearError(); // clear any previous errors
        m_chunk = Mix_LoadWAV(m_file.c_str()); // then try to load the clip
        // if we still got a null, it means there have been errors.
        if(m_chunk == NULL) {
            string s = "Failed to load sound file: `" + m_file + "'";
            // throw the exception to whatever this is calling (ctor anyone?)
            throw GPException(s, Mix_GetError());
        }
    }
}

bool GPSoundClip::isPlaying() const {
    // not an accurate function.
    return Mix_Playing(m_channel);
}

void GPSoundClip::start() {
    m_channel = Mix_PlayChannel(-1, m_chunk, 0);
}
void GPSoundClip::stop() {
    Mix_HaltChannel(m_channel);
    m_channel = -1;
}

}  // namespace gp
