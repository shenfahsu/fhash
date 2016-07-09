// src\HyperEditHash.cpp : 实现文件
//
#include "stdafx.h"
#include "HyperEditHash.h"
#include "Global.h"

// CHyperEditHash

IMPLEMENT_DYNAMIC(CHyperEditHash, CHyperEditHash_BASE_CLASS)

CHyperEditHash::CHyperEditHash()
{
	COLORREF crBlack = RGB(0, 0, 0);
	SetHyperlinkColors(crBlack, crBlack);
}

CHyperEditHash::~CHyperEditHash()
{
}


BEGIN_MESSAGE_MAP(CHyperEditHash, CHyperEditHash_BASE_CLASS)
END_MESSAGE_MAP()



// CHyperEditHash 消息处理程序
BOOL CHyperEditHash::PreTranslateMessage(MSG* pMsg)
{  
    // 编辑框快捷键操作  
    if(WM_KEYDOWN == pMsg->message)   
    {  
		if(::GetFocus() == GetSafeHwnd() && (GetKeyState( VK_CONTROL) & 0xFF00 ) == 0xFF00)   
        {  
            // 全选  
            if( pMsg->wParam == 'A' || pMsg->wParam == 'a')  
            {  
                this->SetSel(0, -1);  
                return true;  
            }  

            // 拷贝  
            if( pMsg->wParam == 'C' || pMsg->wParam == 'c')  
            {  
                this->Copy();  
                return true;  
            }  

            // 剪切  
            if( pMsg->wParam == 'X' || pMsg->wParam == 'x')  
            {  
                this->Cut();  
                return true;  
            }  

            // 粘贴  
            if( pMsg->wParam == 'V' || pMsg->wParam == 'v')  
            {  
                this->Paste();  
                return true;  
            }  

            // 粘贴  
            if( pMsg->wParam == 'Z' || pMsg->wParam == 'z')  
            {  
                this->Undo();  
                return true;  
             }  

        }  
    }  

    return CHyperEditHash_BASE_CLASS::PreTranslateMessage(pMsg);  
 }  

HINSTANCE CHyperEditHash::OpenHyperlink(const CString& hyperlink, CPoint point)
{
	if (hyperlink.IsEmpty())
		return 0;

	ClientToScreen(&point);

	m_cstrLastHyperlink = hyperlink;
	m_cpLastScreenPoint = point;
	
	CWnd *parentWnd = GetParent();
	if (parentWnd != NULL)
	{
		::PostMessage(parentWnd->GetSafeHwnd(), WM_CUSTOM_MSG, WM_HYPEREDIT_MENU, 0);
	}

	return 0;
}

