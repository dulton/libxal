/************************************************************************************\
This source file is part of the KS(X) audio library                                  *
For latest info, see http://libatres.sourceforge.net/                                *
**************************************************************************************
Copyright (c) 2010 Kresimir Spes (kreso@cateia.com), Boris Mikic                     *
*                                                                                    *
* This program is free software; you can redistribute it and/or modify it under      *
* the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php   *
\************************************************************************************/
#ifndef XAL_AUDIOMANAGER_H
#define XAL_AUDIOMANAGER_H

#include <hltypes/harray.h>
#include <hltypes/hstring.h>
#include <map>
#include "xalExport.h"

#define XAL_MAX_SOURCES 16

namespace xal
{
	class Category;
	class Sound;
	class SoundBuffer;
	class Source;

	class xalExport AudioManager
	{
	public:
		AudioManager(chstr deviceName = "");
		~AudioManager();
		
		void logMessage(chstr message);
		hstr getDeviceName() { return this->deviceName; }
		bool isEnabled();
		Category* getCategoryByName(chstr name);
		void createCategory(chstr name, bool streamed = false);
		void setCategoryGain(chstr category, float gain);
		
		void update(float k);
		
		Source* createSource(SoundBuffer* sound);
		void destroySource(Source* source);
		unsigned int allocateSourceId();
		Sound* createSound(chstr filename, chstr categoryName, chstr prefix = "");
		harray<hstr> createSoundsFromPath(chstr path, chstr prefix = "");
		harray<hstr> createSoundsFromPath(chstr path, chstr category, chstr prefix);
		void destroySound(SoundBuffer* sound);
		void destroySoundsWithPrefix(chstr prefix);
		Sound* getSound(chstr name);
		
	protected:
		unsigned int sourceIds[XAL_MAX_SOURCES];
		harray<Source*> sources;
		hstr deviceName;
		std::map<hstr, Category*> categories;
		std::map<hstr, SoundBuffer*> sounds;
		
	};
	
	xalFnExport void init(chstr deviceName = "");
	xalFnExport void destroy();
	xalFnExport void setLogFunction(void (*function)(chstr));
	xalFnExport extern xal::AudioManager* mgr;
}

#endif
