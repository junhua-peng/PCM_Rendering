#ifndef PCM_RENDERING_H
#define PCM_RENDERING_H

#ifdef  PCM_RENDERINGDLL
#define  PCM_RENDERINGDLL extern "C" _declspec(dllimport);
#else
#define  PCM_RENDERINGDLL extern "C" _declspec(dllexport);
#endif

/*
��ʼ��PCM��Ⱦ��
 
*/
PCM_RENDERINGDLL bool pcm_render_init();
 
/* �򻺳���д��pcm���ݲ����ţ�����ʵʱ������
\param  pdata  һ֡pcm���ݣ�һ��Ϊ16λ��ͨ��Ϊ22050���ֽ�
\param  size   һ֡pcm�����ֽڴ�С 
\param  samplerate  pcm���ݲ����� 
\param  channels   pcm����ͨ������ 1Ϊ��ͨ�� 2Ϊ˫ͨ��

*/
PCM_RENDERINGDLL void input_pcmdata_play(void *pdata,long size,long samplerate,long channels);

 
/*
ֹͣ����
*/
PCM_RENDERINGDLL void pcm_stop();

/*��������
*/
PCM_RENDERINGDLL void pcm_render_cleanup();
#endif   

 