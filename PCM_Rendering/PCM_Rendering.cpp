// PCM_Rendering.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "al.h"
#include "alc.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;
#pragma  comment(lib,"OpenAL32.lib")
#define NUMBUFFERS              (4000)
#define	SERVICE_UPDATE_PERIOD	(20)


ALuint		    uiBuffers[NUMBUFFERS];
ALuint		    uiSource;
ALuint			uiBuffer;
ALint			iState;


ALint			iLoop=0;
ALint			iBuffersProcessed, iTotalBuffersProcessed, iQueuedBuffers;
 
unsigned long	ulDataSize = 0;
unsigned long	ulBufferSize=22050;
int num=0;
 


ALCcontext  *m_Context=NULL;
ALCdevice  *m_Device=NULL;
ALuint   m_sourceID;
ALuint bufferID=0;

 
 
bool pcm_render_init()
{
	printf("PCM_Render_Init Success!\n\n");
	if(m_Device==NULL)
	{
		m_Device=alcOpenDevice(NULL);

	}
	else
		return false;
	if(m_Context==NULL)
	{
		if(m_Device)
		{
			m_Context=alcCreateContext(m_Device,NULL);
			alcMakeContextCurrent(m_Context);
		}
	}

	alGenSources( 1, &uiSource );
	alSourcei(uiSource,AL_LOOPING,AL_FALSE);
	alSourcef(uiSource,AL_SOURCE_TYPE,AL_STREAMING);
	alSourcef(uiSource,AL_GAIN,1.0f);
	alDopplerVelocity(1.0);
	//alSpeedOfSound(2.0);

	alGenBuffers( NUMBUFFERS, uiBuffers );
	alGenSources( 1, &uiSource );
	return true;
}
void pcm_play()
{
	alSourcePlay(uiSource);

	iTotalBuffersProcessed = 0;

	 
	
	while (1)
	{
		Sleep( SERVICE_UPDATE_PERIOD );

		 
		iBuffersProcessed = 0;
		alGetSourcei(uiSource, AL_BUFFERS_PROCESSED, &iBuffersProcessed);
 
		iTotalBuffersProcessed += iBuffersProcessed;


		 
		while (iBuffersProcessed)
		{
			 
			uiBuffer = 0;
			alSourceUnqueueBuffers(uiSource, 1, &uiBuffer);

		 

			iBuffersProcessed--;
		}

		 
		alGetSourcei(uiSource, AL_SOURCE_STATE, &iState);
		if (iState != AL_PLAYING)
		{ 
			alGetSourcei(uiSource, AL_BUFFERS_QUEUED, &iQueuedBuffers);
			if (iQueuedBuffers)
			{
				alSourcePlay(uiSource);
			}
			else
			{
				// Finished playing
				break;
			}
		}
	}
}
 
void  pcm_stop()
{
	ALint state;
	alGetSourcei(m_sourceID,AL_SOURCE_STATE,&state);
	if(state!=AL_STOPPED)
	{
		alSourceStop(m_sourceID);
	}
	
}


void pcm_render_cleanup()
{
	printf("\n");
	alDeleteSources(1,&m_sourceID);
	if(m_Context!=NULL)
	{
		alcDestroyContext(m_Context);
		m_Context=NULL;

	}
	if(m_Device)
	{
		alcCloseDevice(m_Device);
		m_Device=NULL;
	}

	alDeleteBuffers(1,&uiSource);
	alDeleteBuffers(1,uiBuffers);
	printf("PCM_Render Exit!");
}
void  input_pcmdata_play(void *pData,long size,long samplerate,long channels)
{
	printf("PCM DATA PLAY...    ");
	
	if(channels==1)
	{
			alBufferData(uiBuffers[iLoop], AL_FORMAT_MONO16, pData, size, samplerate); 
	}
	if(channels==2)
	{
		 alBufferData(uiBuffers[iLoop], AL_FORMAT_STEREO16, pData, size, samplerate);
	}

	alSourceQueueBuffers(uiSource, 1, &uiBuffers[iLoop]);
	iLoop++;
	num++;
	printf("已播放帧数=[%05d]\r",num);
	pcm_play();
}
