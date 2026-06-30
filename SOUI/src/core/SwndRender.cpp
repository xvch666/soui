// SwndRender.cpp -- SWindow RenderTarget / layered-window management.
// Extracted from Swnd.cpp to reduce file size and improve navigability.
#include "souistd.h"
#include "core/SWnd.h"

namespace SOUI
{
	//当窗口有半透明属性并且透明度要需要应用于子窗口时，子窗口的图像渲染到this的缓存RT上。
	BOOL SWindow::IsLayeredWindow() const
	{
		return m_renderCache.m_bLayeredWindow;
	}

	//查询当前窗口内容将被渲染到哪一个渲染层上，没有渲染层时返回NULL
	SWindow * SWindow::_GetCurrentLayeredWindow()
	{
		SWindow *pWnd = this;
		while(pWnd)
		{
			if(pWnd->IsLayeredWindow())
			{
				break;
			}
			pWnd = pWnd->GetParent();
		}

		return pWnd;
	}

	IRenderTarget * SWindow::GetRenderTarget(LPCRECT pRc,DWORD gdcFlags/*=OLEDC_NODRAW*/,BOOL bClientRT/*=TRUE*/)
	{
		CRect rcRT ;        
		if(bClientRT)
		{
			GetClientRect(&rcRT);
		}else
		{
			GetWindowRect(&rcRT);
		}
		if(pRc) rcRT.IntersectRect(pRc,&rcRT);


		CAutoRefPtr<IRegion> rgn;
		GETRENDERFACTORY->CreateRegion(&rgn);
		rgn->CombineRect(rcRT,RGN_COPY);

		return GetRenderTarget(gdcFlags,rgn);
	}

	IRenderTarget * SWindow::GetRenderTarget( DWORD gdcFlags,IRegion *pRgn )
	{
		if (IsUpdateLocked())
		{//return a empty render target
			IRenderTarget *pRT = NULL;
			GETRENDERFACTORY->CreateRenderTarget(&pRT, 0, 0);
			return pRT;
		}

		CRect rcClip;
		pRgn->GetRgnBox(&rcClip);
		SWindow *pParent = GetParent();
		while(pParent)
		{
			rcClip.IntersectRect(rcClip,pParent->GetClientRect());
			pParent = pParent->GetParent();
		}

		pRgn->CombineRect(&rcClip,RGN_AND);
		pRgn->GetRgnBox(&rcClip);

		//获得最近的一个渲染层的RT
		IRenderTarget *pRT = _GetRenderTarget(rcClip,gdcFlags,pRgn);
		BeforePaintEx(pRT);
		return pRT;
	}

	void SWindow::ReleaseRenderTarget(IRenderTarget *pRT)
	{
		if (IsUpdateLocked())
		{
			pRT->Release();
			return;
		}
		SASSERT(m_pGetRTData);
		_ReleaseRenderTarget(pRT);        
	}

	IRenderTarget * SWindow::_GetRenderTarget(CRect & rcGetRT,DWORD gdcFlags,IRegion *pRgn)
	{
		IRenderTarget *pRT = NULL;
		SWindow *pLayerWindow = _GetCurrentLayeredWindow();

		SASSERT(!m_pGetRTData);
		m_pGetRTData = new GETRTDATA;

		m_pGetRTData->gdcFlags = gdcFlags;
		m_pGetRTData->rcRT = rcGetRT;
		m_pGetRTData->rgn = pRgn;

		GetContainer()->BuildWndTreeZorder();

		if(pLayerWindow)
		{
			pRT = pLayerWindow->GetLayerRenderTarget();
		}else
		{
			pLayerWindow = GetRoot();
			pRT = GetContainer()->OnGetRenderTarget(rcGetRT,gdcFlags);
		}

		pRT->PushClipRegion(pRgn,RGN_COPY);

		if(gdcFlags == OLEDC_PAINTBKGND)
		{//重新绘制当前窗口的背景
			pRT->ClearRect(&rcGetRT,0);
			pLayerWindow->_PaintRegion(pRT,pRgn,ZORDER_MIN,m_uZorder);
		}
		return pRT;
	}


	void SWindow::_ReleaseRenderTarget(IRenderTarget *pRT)
	{
		SASSERT(m_pGetRTData);

		SWindow *pRoot = GetRoot();
		SWindow *pLayerWindow = _GetCurrentLayeredWindow();

		if(m_pGetRTData->gdcFlags == OLEDC_PAINTBKGND)
		{//从指定的窗口开始绘制前景
			SWindow * pLayer = pLayerWindow?pLayerWindow:pRoot;
			pLayer->_PaintRegion2(pRT,m_pGetRTData->rgn,(UINT)m_uZorder+1,(UINT)ZORDER_MAX);
		}
		pRT->PopClip();//对应_GetRenderTarget中调用的PushClipRegion

		if(pLayerWindow)
		{//存在一个渲染层
			SASSERT(m_pGetRTData);
			if(m_pGetRTData->gdcFlags != OLEDC_NODRAW)
			{
				UINT uFrgndZorderMin = (UINT)ZORDER_MAX;
				SWindow *pParent = pLayerWindow->GetParent();
				if(pParent)
				{
					//查找上一个渲染层的前景：向上层查找下一个兄弟，直到找到为止
					SWindow *pWnd = pLayerWindow;
					while(pWnd)
					{
						SWindow *pNextSibling = pWnd->GetWindow(GSW_NEXTSIBLING);
						if(pNextSibling)
						{
							uFrgndZorderMin = pNextSibling->m_uZorder;
							break;
						}else
						{
							pWnd = pWnd->GetParent();
						}
					}
				}

				IRenderTarget *pRTRoot = GetContainer()->OnGetRenderTarget(m_pGetRTData->rcRT,OLEDC_OFFSCREEN);
				pRTRoot->PushClipRegion(m_pGetRTData->rgn);
				pRTRoot->ClearRect(m_pGetRTData->rcRT,0);
				//从root开始绘制当前layer前的窗口背景
				pRoot->_PaintRegion2(pRTRoot,m_pGetRTData->rgn,ZORDER_MIN,pLayerWindow->m_uZorder);
				//将layer的渲染更新到root上
				pRTRoot->AlphaBlend(m_pGetRTData->rcRT,pRT,m_pGetRTData->rcRT,pLayerWindow->m_style.m_byAlpha);
				//绘制当前layer前的窗口前景
				if(uFrgndZorderMin!=ZORDER_MAX) 
					pRoot->_PaintRegion2(pRTRoot,m_pGetRTData->rgn,(UINT)uFrgndZorderMin,(UINT)ZORDER_MAX);
				pRTRoot->PopClip();
				GetContainer()->OnReleaseRenderTarget(pRTRoot,m_pGetRTData->rcRT,OLEDC_OFFSCREEN);
			}
		}else
		{//不在绘制层
			GetContainer()->OnReleaseRenderTarget(pRT,m_pGetRTData->rcRT,m_pGetRTData->gdcFlags);
		}
		delete m_pGetRTData;
		m_pGetRTData = NULL;
	}
}
