#include "fmod.hpp"
#include "fmod_errors.h"
	
typedef FMOD::Sound* SoundClass;

class SoundSystem
{
public:
	FMOD::System *m_pSystem;
	SoundSystem();
	bool Initialize();
	void createSound(SoundClass *pSound, const char* pFile);
	void playSound(SoundClass pSound, bool bLoop);
	void releaseSound(SoundClass pSound);
private:

};

