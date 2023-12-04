#include "SoundManager.h"

void SoundManager::LoadDir(W_STR path)
{
	struct _wfinddata_t file;
	intptr_t handle = _wfindfirst((path + L"*.*").c_str(), &file);

	if (handle == -1L) return;

	do {
		if ((file.attrib & _A_SUBDIR) && file.name[0] != '.')
		{
			LoadDir(path + file.name + L"/");
		}
		else if (file.name[0] != '.')
		{
			_filePaths.push_back(path + file.name);
		}
	} while (_wfindnext(handle, &file) == 0);
	_findclose(handle);
}

void SoundManager::LoadAll(W_STR path)
{
	LoadDir(path);
	for (auto& filePath : _filePaths)
		LoadSound(filePath);
}

Sound* SoundManager::LoadSound(W_STR filePath)
{
	W_STR fileName = GetFileName(filePath);

	auto iter = _sounds.find(fileName);
	if (iter != _sounds.end())
	{
		return iter->second;
	}
	else
	{
		Sound* sound = new Sound;
		sound->_name = filePath;
		HRESULT result = sound->Load(_system, filePath);
		if (SUCCEEDED(result))
			_sounds.insert(std::make_pair(fileName, sound));
		return sound;
	}
}

T_STR SoundManager::GetFileName(W_STR filePath)
{
	TCHAR drive[MAX_PATH]		= { 0, };
	TCHAR dir[MAX_PATH]			= { 0, };
	TCHAR fileName[MAX_PATH]	= { 0, };
	TCHAR ext[MAX_PATH]			= { 0, };

	_tsplitpath_s(filePath.c_str(),
		drive, dir, fileName, ext);

	return W_STR(fileName) + ext;
}

Sound* SoundManager::GetSoundPtr(W_STR fileName)
{
	auto sound = _sounds.find(fileName);
	if (sound != _sounds.end())
		return sound->second;
	else return nullptr;
}

bool SoundManager::Init()
{
	FMOD::System_Create(&_system);
	_system->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

bool SoundManager::Frame()
{
	_system->update();
	for (auto sound : _sounds)
	{
		if (sound.second)
			sound.second->Frame();
	}
	return true;
}

bool SoundManager::Release()
{
	for (auto sound : _sounds)
	{
		if (sound.second)
			sound.second->Release();
		delete sound.second;
	}
	_system->close();
	_system->release();
	_sounds.clear();
	return true;
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	Release();
}
