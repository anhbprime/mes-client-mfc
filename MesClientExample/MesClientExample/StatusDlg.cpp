#include "pch.h"
#include "StatusDlg.h"
#include "afxdialogex.h"
#include "MesMessages.h"
#include <memory>

IMPLEMENT_DYNAMIC(CStatusDlg, CDialogEx)

CStatusDlg::CStatusDlg(CWnd* pParent) : CDialogEx(IDD_STATUSDLG, pParent) {}
CStatusDlg::~CStatusDlg() {}

void CStatusDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, list1);
    DDX_Control(pDX, IDC_LIST2, list2);
}

BEGIN_MESSAGE_MAP(CStatusDlg, CDialogEx)
    ON_MESSAGE(WM_IO_EVENT, &CStatusDlg::OnIoEvent)
    ON_MESSAGE(WM_MES_REPLY, &CStatusDlg::OnMesReply)
END_MESSAGE_MAP()

void CStatusDlg::AppendLine(const CString& s) {
    CString now; 
    now.Format(L"[Status] %s", s.GetString());
    SetWindowText(now);
}

LRESULT CStatusDlg::OnIoEvent(WPARAM, LPARAM lParam) {
    auto* p = reinterpret_cast<IoEventPayload*>(lParam);

    ASSERT_VALID(this);
    ASSERT(list1.GetSafeHwnd() != nullptr);

    CString s;
    if (p) {
        TRACE(L"[OnIoEvent] p=%p id=%s signal=%s\n",
            p,
            p->id.GetString(),
            p->signal.GetString());

        s.Format(L"IOEvent id=%s signal=%s", p->id.GetString(), p->signal.GetString());
        list1.AddString(s);
        if (list1.GetCount() > 5) {
            list1.DeleteString(0);
        }
        delete p;
    }
    else {
        TRACE(L"[OnIoEvent] p is null! lParam=%p\n", lParam);
    }
    return 0;
}

LRESULT CStatusDlg::OnMesReply(WPARAM wParam, LPARAM lParam)
{
    auto op = static_cast<MesOpCode>(wParam);
    std::unique_ptr<MesBase> msg(reinterpret_cast<MesBase*>(lParam));

    switch (op)
    {
    case MesOpCode::RecipeDownload:
    {
        auto* p = static_cast<MesRecipeDownloadMsg*>(msg.get());

        TRACE(L"[OnMesReply] p=%p RecipeName=%s Version=%d\n",
            p,
            p->RecipeName().c_str(),
            p->Version());

        CString text;
        text.Format(_T("Recipe: %S / Ver: %d"),
            p->RecipeName().c_str(),
            p->Version());
        list2.AddString(text);
        if (list2.GetCount() > 5) {
            list2.DeleteString(0);
        }
        break;
    }
    case MesOpCode::Alarm:
    {
        break;
    }
    default:
        break;
    }

    return 0;
}