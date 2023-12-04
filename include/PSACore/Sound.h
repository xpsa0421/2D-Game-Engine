#pragma once
#include <tchar.h>
#include "Std.h"
#include "fmod/fmod.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#pragma comment (lib, "fmod_vc.lib")

class Sound
{
public:
	FMOD::System*	_system		= nullptr;
	FMOD::Sound*	_sound		= nullptr;
	FMOD::Channel*	_channel	= nullptr;
	W_STR			_name;
	float			_volume;
	unsigned int	_length;
	W_STR			_buffer;
public:
	bool	IsPlaying();
	bool	StartPlay(bool isLooped);
	void	PlayPause();
	void	Stop();
	void	VolumeUp(float amount = 0.1f);
	void	VolumeDown(float amount = 0.1f);
	void	SetLoop(bool isLooped);
public:
	virtual bool	Load(FMOD::System* system, W_STR fileName);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

