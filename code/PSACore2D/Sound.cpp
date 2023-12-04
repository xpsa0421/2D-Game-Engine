#include "Sound.h"

bool Sound::IsPlaying()
{
	bool playing = false;
	if (_channel == nullptr) _channel->isPlaying(&playing);
	return playing;
}

bool Sound::StartPlay(bool isLooped)
{
	if (!IsPlaying())
	{
		FMOD_RESULT result = _system->playSound(
			_sound, nullptr, false, &_channel
		);
		if (result == FMOD_OK)
		{
			_volume = 1.0f;
			_channel->setVolume(_volume);
			SetLoop(isLooped);
		}
	}
	return true;
}

void Sound::PlayPause()
{
	if (_channel == nullptr) return;
	bool paused;
	_channel->getPaused(&paused);
	_channel->setPaused(!paused);
}

void Sound::Stop()
{
	_channel->stop();
}

void Sound::VolumeUp(float amount)
{
	_volume += amount;
	_volume = min(1.0f, _volume);
	_channel->setVolume(_volume);
}

void Sound::VolumeDown(float amount)
{
	_volume -= amount;
	_volume = max(0.0f, _volume);
	_channel->setVolume(_volume);
}

void Sound::SetLoop(bool isLooped)
{
	if (isLooped)
		_sound->setMode(FMOD_LOOP_NORMAL);
	else
		_sound->setMode(FMOD_LOOP_OFF);
}

bool Sound::Load(FMOD::System* system, W_STR fileName)
{
	_system = system;
	FMOD_RESULT result = _system->createSound(
		wtm(fileName).c_str(),
		FMOD_DEFAULT, nullptr, &_sound);

	if (result == FMOD_OK)
	{
		_sound->getLength(&_length, FMOD_TIMEUNIT_MS);
	}
	return true;
}

bool Sound::Init()
{
	return true;
}

bool Sound::Frame()
{
	if (_channel)
	{
		unsigned int playTime = 0;
		_channel->getPosition(&playTime, FMOD_TIMEUNIT_MS);
		TCHAR buffer[256] = { 0, };
		_stprintf_s(buffer,
			_T("재생시간[%02d:%02d:%02d]\n전체길이[%02d:%02d:%02d]"),
			playTime / 1000 / 60,
			playTime / 1000 % 60,
			playTime / 10   % 60,
			_length  / 1000 / 60,
			_length  / 1000 % 60,
			_length  / 10   % 60
		);
		_buffer = buffer;
	}
	return true;
}

bool Sound::Render()
{
	return true;
}

bool Sound::Release()
{
	if (_sound)	_sound->release();
	return true;
}