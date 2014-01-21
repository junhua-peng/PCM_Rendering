#ifndef PCM_RENDERING_H
#define PCM_RENDERING_H

#ifdef  PCM_RENDERINGDLL
#define  PCM_RENDERINGDLL extern "C" _declspec(dllimport);
#else
#define  PCM_RENDERINGDLL extern "C" _declspec(dllexport);
#endif

/*
初始化PCM渲染库
 
*/
PCM_RENDERINGDLL bool pcm_render_init();
 
/* 向缓冲区写入pcm数据并播放，用于实时流播放
\param  pdata  一帧pcm数据，一般为16位单通道为22050个字节
\param  size   一帧pcm数据字节大小 
\param  samplerate  pcm数据采样率 
\param  channels   pcm数据通道个数 1为单通道 2为双通道

*/
PCM_RENDERINGDLL void input_pcmdata_play(void *pdata,long size,long samplerate,long channels);

 
/*
停止播放
*/
PCM_RENDERINGDLL void pcm_stop();

/*清理数据
*/
PCM_RENDERINGDLL void pcm_render_cleanup();
#endif   

 