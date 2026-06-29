//SOUI组件配置

#pragma  once

#define DLL_SOUI_COM
#include <string/tstring.h>
#include <commask.h>

#ifndef SCOM_MASK
#define SCOM_MASK scom_mask_scom_all
#endif 

#define COM_IMGDECODER  _T("imgdecoder-gdip")

#ifdef _WIN64
#ifdef _DEBUG
#define COM_RENDER_GDI  _T("render-gdi64d.dll")
#define COM_RENDER_SKIA _T("render-skia64d.dll")
#define COM_TRANSLATOR _T("translator64d.dll")
#define COM_LOG4Z   _T("log4z64d.dll")
#define COM_TASKLOOP _T("taskloop64d.dll")
#define COM_IPCOBJ _T("sipcobject64d.dll")
#else
#define COM_RENDER_GDI  _T("render-gdi64.dll")
#define COM_RENDER_SKIA _T("render-skia64.dll")
#define COM_TRANSLATOR _T("translator64.dll")
#define COM_LOG4Z   _T("log4z64.dll")
#define COM_TASKLOOP _T("taskloop64.dll")
#define COM_IPCOBJ _T("sipcobject64.dll")
#endif
#else
#ifdef _DEBUG
#define COM_RENDER_GDI  _T("render-gdid.dll")
#define COM_RENDER_SKIA _T("render-skiad.dll")
#define COM_TRANSLATOR _T("translatord.dll")
#define COM_LOG4Z   _T("log4zd.dll")
#define COM_TASKLOOP _T("taskloopd.dll")
#define COM_IPCOBJ _T("sipcobjectd.dll")
#else
#define COM_RENDER_GDI  _T("render-gdi.dll")
#define COM_RENDER_SKIA _T("render-skia.dll")
#define COM_TRANSLATOR _T("translator.dll")
#define COM_LOG4Z   _T("log4z.dll")
#define COM_TASKLOOP _T("taskloop.dll")
#define COM_IPCOBJ _T("sipcobject.dll")
#endif
#endif


#ifdef LIB_SOUI_COM
#pragma message("LIB_SOUI_COM")

#pragma comment(lib,"Usp10")
#pragma comment(lib,"opengl32")

#ifdef _DEBUG
#if(SCOM_MASK&scom_mask_render_skia)
    #pragma comment(lib,"skiad")
    #pragma comment(lib,"render-skiad")
#endif
#if(SCOM_MASK&scom_mask_render_gdi)
    #pragma comment(lib,"render-gdid")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_wic)
    #pragma comment(lib,"imgdecoder-wicd")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_png)
    #pragma comment(lib,"pngd")
	#pragma comment(lib,"zlibd")
    #pragma comment(lib,"imgdecoder-pngd")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_stb)
    #pragma comment(lib,"imgdecoder-stbd")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_gdip)
    #pragma comment(lib,"imgdecoder-gdipd")
#endif
#if(SCOM_MASK&scom_mask_translator)
    #pragma comment(lib,"translatord")
#endif
#if(SCOM_MASK&scom_mask_log4z)
    #pragma comment(lib,"log4zd")
#endif
#if(SCOM_MASK&scom_mask_taskloop)
	#pragma comment(lib,"taskloopd")
#endif
#if(SCOM_MASK&scom_mask_ipcobject)
	#pragma comment(lib,"sipcobjectd")
#endif
#else//_DEBUG
#if(SCOM_MASK&scom_mask_render_skia)
    #pragma comment(lib,"skia")
    #pragma comment(lib,"render-skia")
#endif
#if(SCOM_MASK&scom_mask_render_gdi)
    #pragma comment(lib,"render-gdi")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_wic)
    #pragma comment(lib,"imgdecoder-wic")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_png)
    #pragma comment(lib,"png")
	#pragma comment(lib,"zlib")
    #pragma comment(lib,"imgdecoder-png")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_stb)
    #pragma comment(lib,"imgdecoder-stb")
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_gdip)
    #pragma comment(lib,"imgdecoder-gdip")
#endif
#if(SCOM_MASK&scom_mask_translator)
    #pragma comment(lib,"translator")
#endif
#if(SCOM_MASK&scom_mask_log4z)
    #pragma comment(lib,"log4z")
#endif
#if(SCOM_MASK&scom_mask_taskloop)
	#pragma comment(lib,"taskloop")
#endif
#if(SCOM_MASK&scom_mask_ipcobject)
	#pragma comment(lib,"sipcobject")
#endif
#endif//_DEBUG

namespace SOUI
{
    namespace IMGDECODOR_WIC
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace IMGDECODOR_STB
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace IMGDECODOR_PNG
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace IMGDECODOR_GDIP
    {
        BOOL SCreateInstance(IObjRef **);
    }

    namespace RENDER_GDI
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace RENDER_SKIA
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace TRANSLATOR
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace LOG4Z
    {
        BOOL SCreateInstance(IObjRef **);
    }
	namespace TASKLOOP {
		BOOL SCreateInstance(IObjRef **);
	}
	namespace IPC {
		BOOL SCreateInstance(IObjRef **);
	}
}//end of soui

class SComMgr2
{
public:
    SComMgr2(LPCTSTR pszImgDecoder = NULL):m_strImgDecoder(pszImgDecoder)
    {
    }

	void SetDllPath(const SOUI::SStringT & strDllPath){}

    BOOL CreateImgDecoder(IObjRef ** ppObj)
    {
#if(SCOM_MASK&scom_mask_imgdecoder_wic)
        if(m_strImgDecoder == _T("imgdecoder-wic"))
            return SOUI::IMGDECODOR_WIC::SCreateInstance(ppObj);
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_stb)
        if(m_strImgDecoder == _T("imgdecoder-stb"))
            return SOUI::IMGDECODOR_STB::SCreateInstance(ppObj);
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_png)
        if(m_strImgDecoder == _T("imgdecoder-png"))
            return SOUI::IMGDECODOR_PNG::SCreateInstance(ppObj);
#endif
#if(SCOM_MASK&scom_mask_imgdecoder_gdip)
        if(m_strImgDecoder == _T("imgdecoder-gdip"))
            return SOUI::IMGDECODOR_GDIP::SCreateInstance(ppObj);
#endif
         SASSERT(0);
         return FALSE;
    }

#if(SCOM_MASK&scom_mask_render_gdi)
    BOOL CreateRender_GDI(IObjRef **ppObj)
    {
        return SOUI::RENDER_GDI::SCreateInstance(ppObj);
    }
#endif

#if(SCOM_MASK&scom_mask_render_skia)
    BOOL CreateRender_Skia(IObjRef **ppObj)
    {
        return SOUI::RENDER_SKIA::SCreateInstance(ppObj);
    }
#endif


#if(SCOM_MASK&scom_mask_translator)
    BOOL CreateTranslator(IObjRef **ppObj)
    {
        return SOUI::TRANSLATOR::SCreateInstance(ppObj);
    }
#endif



    
#if(SCOM_MASK&scom_mask_log4z)
    BOOL CreateLog4z(IObjRef **ppObj)
    {
        return SOUI::LOG4Z::SCreateInstance(ppObj);
    }
#endif

#if(SCOM_MASK&scom_mask_taskloop)
	BOOL CreateTaskLoop(IObjRef **ppObj)
	{
		return SOUI::TASKLOOP::SCreateInstance(ppObj);
	}
#endif
#if(SCOM_MASK&scom_mask_ipcobject)
	BOOL CreateIpcObject(IObjRef **ppObj)
	{
		return SOUI::IPC::SCreateInstance(ppObj);
	}
#endif
	SOUI::SStringT m_strImgDecoder;
};

#else
	
#include <com-loader.hpp>


class SComMgr2
{
public:
    SComMgr2(LPCTSTR pszImgDecoder = NULL)
    {
        if(pszImgDecoder) m_strImgDecoder = pszImgDecoder;
        else m_strImgDecoder = COM_IMGDECODER;
    }

	void SetDllPath(const SOUI::SStringT & strDllPath)
	{
		m_strDllPath = strDllPath;
		if(!m_strDllPath.IsEmpty())
		{
			if(m_strDllPath.Right(1)!=_T("\\"))
			{
				m_strDllPath+=_T("\\");
			}
		}
	}

    BOOL CreateImgDecoder(IObjRef ** ppObj)
    {
#ifdef _WIN64
#ifdef _DEBUG
        SOUI::SStringT strImgDecoder = m_strImgDecoder+_T("64d.dll");
#else
        SOUI::SStringT strImgDecoder = m_strImgDecoder+_T("64.dll");
#endif
#else
#ifdef _DEBUG
        SOUI::SStringT strImgDecoder = m_strImgDecoder+_T("d.dll");
#else
        SOUI::SStringT strImgDecoder = m_strImgDecoder+_T(".dll");
#endif
#endif
        return imgDecLoader.CreateInstance(m_strDllPath+strImgDecoder,ppObj);
    }
    
    BOOL CreateRender_GDI(IObjRef **ppObj)
    {
        return renderLoader.CreateInstance(m_strDllPath+COM_RENDER_GDI,ppObj);
    }

    BOOL CreateRender_Skia(IObjRef **ppObj)
    {
        return renderLoader.CreateInstance(m_strDllPath+COM_RENDER_SKIA,ppObj);
    }

    BOOL CreateTranslator(IObjRef **ppObj)
    {
        return transLoader.CreateInstance(m_strDllPath+COM_TRANSLATOR,ppObj);
    }

	
    BOOL CreateLog4z(IObjRef **ppObj)
    {
        return log4zLoader.CreateInstance(m_strDllPath+COM_LOG4Z,ppObj);
    }

	BOOL CreateTaskLoop(IObjRef **ppObj)
	{
		return taskLoopLoader.CreateInstance(m_strDllPath + COM_TASKLOOP, ppObj);
	}

	BOOL CreateIpcObject(IObjRef **ppObj)
	{
		return ipcLoader.CreateInstance(m_strDllPath + COM_IPCOBJ, ppObj);
	}
protected:
    //SComLoader实现从DLL的指定函数创建符号SOUI要求的类COM组件。
    SComLoader imgDecLoader;
    SComLoader renderLoader;
    SComLoader transLoader;
    SComLoader log4zLoader;
	SComLoader taskLoopLoader;
	SComLoader ipcLoader;

    SOUI::SStringT m_strImgDecoder;
	SOUI::SStringT m_strDllPath;
};
#endif
