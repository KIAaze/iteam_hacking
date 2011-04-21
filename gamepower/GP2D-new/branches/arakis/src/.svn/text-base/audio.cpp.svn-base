#include "audio.h"
#include "core.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace gp2d {

GP2DAudioManager* GP2DAudioManager::m_instance = NULL;

GP2DAudioManager::GP2DAudioManager() {
    // initialize defaults:
    m_buffers = 4096;
    m_frequency = 48000;
    m_channels = 4;
    m_format = AUDIO_S16;
    m_mixingChannels = 16;
    m_isInit = false;
}

GP2DAudioManager::~GP2DAudioManager() {
    closeAudio();
}

GP2DAudioManager* GP2DAudioManager::getInstance() {
    if(m_instance == NULL) {
        m_instance = new GP2DAudioManager();
    }
    return m_instance;
}

void GP2DAudioManager::openAudio() throw (GP2DException) {
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
        throw GP2DException(ss.str(), s);
    }




    // allocate the default amount of mixing channels
    setMixChannels(m_mixingChannels);

    m_isInit = true; // set initialized flag.
}

void GP2DAudioManager::closeAudio() {
    Mix_CloseAudio();
}

void GP2DAudioManager::setFormat(GP2DAudioFormat format) {
    m_format = format;
}

void GP2DAudioManager::setChannels(int channels) {
    m_channels = channels;
}

void GP2DAudioManager::setChunkSize(int chunkSize) {
    m_buffers = chunkSize;
}

void GP2DAudioManager::setFrequency(int frequency) {
    m_frequency = frequency;
}

void GP2DAudioManager::setMixChannels(int num) {
    m_mixingChannels = num;
    if(num >= 0) {
        Mix_AllocateChannels(num);
    }
}

void GP2DAudioManager::setMasterVolume(int volume) {
    Mix_Volume(-1, volume);
    Mix_VolumeMusic(volume);
}

int GP2DAudioManager::getMasterVolume() {
    return Mix_Volume(-1, -1);
}

int GP2DAudioManager::getMixChannels() {
    // Mix_AllocateChannels(-1) can also be used to retrieve the channels.
    // Which is perhaps a better way, because this Mix_AllocateChannels can
    // also be used outside of GP2D. Values will then be inconsequent.
    return Mix_AllocateChannels(-1);
}

bool GP2DAudioManager::isInitialized() {
    return m_isInit;
}

//==============================================================================

GP2DAudioClip::GP2DAudioClip(string file) throw (GP2DException) {
    m_file = file;
}

GP2DAudioClip::~GP2DAudioClip() {

}
const string& GP2DAudioClip::getFile() {
    return m_file;
}

void GP2DAudioClip::setFile(const string& file) {
    m_file = file;
}

void GP2DAudioClip::setLoops(const int loops) {
    m_loops = loops;
}

//==============================================================================

GP2DMusicClip::GP2DMusicClip(string file) throw (GP2DException) : GP2DAudioClip(file) {
	m_music = NULL; // set this stuff initially to null.
    try {
        init();
    } catch(GP2DException& ex) {
        throw; // rethrow it!
    }
}

GP2DMusicClip::~GP2DMusicClip() {
    if(m_music == NULL) {
        clog << "GP2D: Music was not loaded" << endl;
        return;
    }

    if(isPlaying()) {
        stop();
    }
    Mix_FreeMusic(m_music);
    m_music = NULL;
}

void GP2DMusicClip::init() throw (GP2DException) {
    if(m_music == NULL) {
        SDL_ClearError(); // clear any previous errors
        m_music = Mix_LoadMUS(m_file.c_str()); // then try to load the music.
        // if we still got a null, it means there have been errors.
        if(m_music == NULL) {
            string s = "Failed to load music file: `" + m_file + "'";
            // throw the exception to whatever this is calling (ctor anyone?)
            throw GP2DException(s, Mix_GetError());
        }
    }
}

void GP2DMusicClip::start() {
    if(!isPlaying()) {
        Mix_PlayMusic(m_music, -1);
    } else {
        cerr << "Cannot play two types of music simultaneously" << endl;
    }
}

void GP2DMusicClip::stop() {
    Mix_HaltMusic();
}

bool GP2DMusicClip::isPlaying() {
    return Mix_PlayingMusic() == 1 ? true : false;
}

//==============================================================================

GP2DSoundClip::GP2DSoundClip(string file) throw (GP2DException) : GP2DAudioClip(file) {
    m_channel = -1;
    // m_chunk has to explicitly be set to null, or else it
    // has an undefined value of something which is not null.
    m_chunk = NULL;
    try {
        init();
    } catch(GP2DException& ex) {
        throw ex;
    }
}

GP2DSoundClip::~GP2DSoundClip() {
    // only free the chunk if it is not null.
    if(m_chunk != NULL) {
        Mix_FreeChunk(m_chunk);
    }
    m_chunk = NULL;
}

void GP2DSoundClip::init() throw (GP2DException) {
    if(m_chunk == NULL) {
        SDL_ClearError(); // clear any previous errors
        m_chunk = Mix_LoadWAV(m_file.c_str()); // then try to load the clip
        // if we still got a null, it means there have been errors.
        if(m_chunk == NULL) {
            string s = "Failed to load sound file: `" + m_file + "'";
            // throw the exception to whatever this is calling (ctor anyone?)
            throw GP2DException(s, Mix_GetError());
        }
    }
}

bool GP2DSoundClip::isPlaying() {
    // not an accurate function.
    return Mix_Playing(m_channel);
}

void GP2DSoundClip::start() {
    m_channel = Mix_PlayChannel(-1, m_chunk, 0);
}
void GP2DSoundClip::stop() {
    Mix_HaltChannel(m_channel);
    m_channel = -1;
}

}  // namespace gp2d
