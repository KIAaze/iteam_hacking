#ifndef AUDIO_H_
#define AUDIO_H_

#include <string>
#include <SDL/SDL_mixer.h>

#include "core.h"

namespace gp {

/**
 * The audio manager is responsible for managing the audio clips (sound and
 * music). It is declared as a singleton since we only want one audio manager
 * in an application. This manager is supposed to keep a list of all the loaded
 * sound files so they can be stopped all at once and deleted all at once.
 *
 * @author krpors
 */
class GPAudioManager {
protected:

    /// The one and only instance of the GPAudioManager class.
    static GPAudioManager* m_instance;

private:

    gpBool m_isInit;

    /// The rate of fire.
    gpInt32 m_frequency;

    /// The audio formatting (see the enumeration GPAudioFormat in this class
    gpUshort m_format;

    /// The amount of channels: 1: mono, 2=stereo. XXX: enum or something
    gpInt32 m_channels; // = 2;

    /// The buffer stuff. XXX read up on this
    gpInt32 m_buffers; // = 4096;

    /// Amount of playable channels (allocated by SDL).
    gpInt32 m_mixingChannels;


    /**
     * Constructs the GPAudioManager. Declared private so nobody can instantiate
     * another instance of this class.
     */
    GPAudioManager();
public:

    ~GPAudioManager();

    /**
     * Available audio formats.
     */
    enum GPAudioFormat {
        /// Unnsigned 8 bit samples
        GP_AUDIO_U8 = AUDIO_U8,
        /// Signed 8 bit samples
        GP_AUDIO_S8 = AUDIO_S8,
        /// Unsigned 16 bit samples
        GP_AUDIO_U16LSB = AUDIO_U16LSB,
        /// Signed 16 bit samples
        GP_AUDIO_S16LSB = AUDIO_S16LSB,
        /// Unsigned 16 bit samples, big-endian byte order
        GP_AUDIO_U16MSB = AUDIO_U16MSB,
        /// Signed 16 bit samples, big-endian byte order
        GP_AUDIO_S16MSB = AUDIO_S16MSB,
        /// Unsigned 16 bit samples, same as GP_AUDIO_U16LSB
        GP_AUDIO_U16 = AUDIO_U16,
        /// Signed 16 bit samples, same as GP_AUDIO_S16LSB
        GP_AUDIO_S16 = AUDIO_S16,
    };

    /**
     * Gets the one and only instance of ths GPAudioManager.
     *
     * @return a pointer to the GPAudioManager instance.
     */
    static GPAudioManager* getInstance();

    /**
     * Basic initialization of the manager. Opens the audio for usage.
     *
     * @throw GPException when audio device can not be opened, and
     *  things like that.
     */
    void openAudio() throw (GPException);

    /**
     * Closes the audio.
     */
    void closeAudio();

    /**
     * Sets the playformat. Note that this has to be done before
     * initializing, because init() uses this format afterwards. The default
     * value is set to GPAudioFormat::GP_AUDIO_S16.
     *
     * @param format The format as in one of the GPAudioFormat enumeration.
     */
    void setFormat(GPAudioFormat format);

    /**
     * Sets the amount of channels to use for output (1 = mono, 2 = audio, etc?).
     *
     * @param channels The amount of output channels to use.
     */
    void setChannels(gpInt32 channels);

    /**
     * Sets the chunksize for playback/buffering. Low values mean more sound
     * skipping, but too high of values mean more sound is being buffered, resulting
     * in more memory usage iirc.
     *
     * @param chunkSize The chunksize. Default is 4096.
     */
    void setChunkSize(gpInt32 chunkSize);

    /**
     * Sets the frequence to use for playback. Values are most likely to hold any
     * of these values: 8000, 11025, 22050, 32000, 44056, 44100, 47250, 48000,
     * 50000, 50400, 88200 hertz. Default is 48000.
     *
     * @param The frequency in hertz.
     */
    void setFrequency(gpInt32 frequency);

    /**
     * Sets the amount of channels to use for mixing. This can be called
     * multiple times, even with sounds playing. If num is less than the
     * current number of channels, then the higher channels will be stopped,
     * freed, and therefore not mixed any longer. It's probably not a good
     * idea to change the size 1000 times a second though. This function only
     * accepts values higher than zero. If a zero or a negative number is used,
     * nothing happens.
     *
     * @param num The number of mixing channels to allocate.
     */
    void setMixChannels(gpInt32 num);

    /**
     * Returns the amount of mixing channels which are currently allocated.
     *
     * @return the mixing channels currently allocated.
     */
    int getMixChannels();

    /**
     * Sets the master volume.
     *
     * @param volume The volume, between 0 and 128.
     */
    void setMasterVolume(gpInt32 volume);

    /**
     * Gets the master volume.
     *
     * @return The master volume.
     */
    gpInt32 getMasterVolume();

    /**
     * Returns true when the audio backend is initialized successfully after the
     * call init(), and false if otherwise.
     *
     * @return true when initialized and false if not.
     */
    gpBool isInitialized();
};

/**
 * A generic interface for an audio clip. An audio clip can generally be either
 * a music score, or a chunk of a sound clip (i.e. effects). This separation is
 * also done in GP, because (currently) the audio backend is SDL, which also
 * maintains this view on audio. Don't ask me why; I just adapted to it.
 *
 * @author krpors
 */
class GPAudioClip {

protected:

    /// The file which is supposed to be loaded.
    std::string m_file;

    /**
     * The amount of loops for this audio clip. GP_FOREVER is used for an
     * unlimited amount of loopage.
     */
    gpInt32 m_loops;

public:

    /**
     * Constructor for GPAudioClip. Takes a std::string to a file which
     * is supposed to be loaded. Note that the actual loading of the file
     * should be done in the protected virtual function init().
     *
     * @param file The file to be loaded.
     * @throws GPException when the virtual init() function was not able
     *  to load the given file.
     */
    GPAudioClip(std::string file) throw (GPException);

    /**
     * Virtual destructor. Needs to clean up this mess. That's whe SHE said!
     */
    virtual ~GPAudioClip();

    /**
     * Starts the audio playback.
     */
    virtual void start() = 0;

    /**
     * Checks whether the audio clip is playing or not.
     *
     * @return true when the audio is played back, or false if not.
     */
    virtual bool isPlaying() const = 0;

    /**
     * Attempts to stop the audio playback of this clip.
     */
    virtual void stop() = 0;

    /// Constant for a 'forever' loop, i.e. ~66535
    static const gpInt32 GP_FOREVER = -1;

    /**
     * Returns the file which is used for loading this audio clip.
     *
     * @return The file.
     */
    const std::string& getFile() const;

    /**
     * Sets the file.
     *
     * @param file The file to set.
     */
    void setFile(const std::string& file);

    /**
     * Sets the amount of loops in the audio clip. Use the constant
     * GPAudioClip::GP_FOREVER to loop... well... for a long time.
     * Mind that the audio chunk or whatever has to be reinitialized
     * after this call, since this only sets a property on the class.
     *
     * @param loops The amount of loops to do.
     */
    void setLoops(const gpInt32 loops);
};


/**
 * Since the audio backend provided by SDL (which is SDL_mixer) provides a
 * seperate function for playing music, this class was created which describes
 * the interface to a music clip. This music inherits properties from the
 * GPAudioClip class. Since there can be played only one music 'stream' at
 * a time (SDL prevents from playing multiple music streams at once), the user
 * of this class needs to know that the previous music streams needs to be
 * stopped/closed whatever.
 *
 * TODO: more documentation, and some finishing up coding.
 *
 * @author krpors
 */
class GPMusicClip : public GPAudioClip {
private:

    /// The music struct pointer, which is NULL at start.
    Mix_Music* m_music;

    /**
     * Initializer.
     */
    void init() throw (GPException);

public:

    /**
     * Creates a music clip using the file to load data from.
     *
     * @param file The file to load.
     * @throws GPException When the music clip could not be loaded.
     */
    GPMusicClip(std::string file) throw (GPException);

    /**
     * Destsroys this music clip by freeing resources.
     */
    ~GPMusicClip();

    /**
     * Starts this music clip.
     */
    void start();

    /**
     * Returns whether this music clip is playing. XXX: currently, this
     * function returns whether *any* music is playing at all.
     *
     * @return true when ANY music is played at all (hooray for procedural
     *  programming :-/ ), and false if otherwise.
     */
    gpBool isPlaying() const;

    /**
     * Stops the playing of ANY music out there. XXX: yes, it stops any music
     * which is playing, even if it was not started through this specific
     * instance of this class.
     */
    void stop();
};


/**
 * Just like the music clip class: the audio backend provided by SDL
 * (which is SDL_mixer) provides a seperate function for playing sound clips.
 * This class was created to describe such a sound clip. This music inherits
 * properties from the GPAudioClip class.
 *
 * When a soundclip is played through SDL_mixer (which is hidden from the user
 * of this class), it is played through a so-called channel. In these sound
 * clips, two things can arise here:
 *
 * - Make use of the same, allocated channel (for instance, 4) to play back the
 *   sample
 * - Allocate a different channel for each time the sound clip is played.
 *
 * Method one: this will stop the currenet allocated channel to play back the
 * sound clip again on the _same_ channel; this means the same clip can not be
 * played 'over eachother'.
 *
 * Method two: this will allocate a different channel for each playback, which
 * mean sounds can 'overlap' each other.
 *
 * Currently, I've chosen to do method two since it's a bit more versatile. Both
 * of these options need to be implemented though I guess in the future, but don't
 * know yet how to.
 *
 * @author krpors
 */
class GPSoundClip : public GPAudioClip {
private:

    /// The mix chunk.
    Mix_Chunk* m_chunk;

    /**
     * Every sound that gets played is assigned to a channel.  Note that
     * this is different from the number of channels you request when you
     * open the audio device; a channel in SDL_mixer holds information
     * about a sound sample that is playing, while the number of channels
     * you request when opening the device is dependent on what sort of
     * sound you want (1 channel = mono, 2 = stereo, etc)
     */
    gpInt32 m_channel;

    /**
     * Initializes the sound clip.
     */
    void init() throw (GPException);


public:

    /**
     * Creates a sound clip using the file to load data from.
     *
     * @param file The file to load.
     * @throws GPException When the sound clip could not be loaded.
     */
    GPSoundClip(std::string file) throw (GPException);

    /**
     * Destroys the sound clip.
     */
    ~GPSoundClip();

    /**
     * Starts playback of this clip.
     */
    void start();

    /**
     * Returns whether this clip is playing. FIXME: this is not really
     * applicable since a new channel is used each time after playing.
     * It has inaccurate results.
     *
     * @return true or false.
     */
    gpBool isPlaying() const;

    /**
     * Stops the clip. Inaccurate results because it tried to stop a channel
     * which has been LAST allocated by start().
     */
    void stop();
};



}  // namespace gp

#endif /*AUDIO_H_*/
