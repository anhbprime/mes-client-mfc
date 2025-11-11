#include "pch.h"
#include "StatusDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CStatusDlg, CDialogEx)

CStatusDlg::CStatusDlg(CWnd* pParent) : CDialogEx(IDD_STATUSDLG, pParent) {}
CStatusDlg::~CStatusDlg() {}

void CStatusDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStatusDlg, CDialogEx)
    ON_MESSAGE(WM_IO_EVENT, &CStatusDlg::OnIoEvent)
    ON_MESSAGE(WM_MES_REPLY, &CStatusDlg::OnMesReply)
END_MESSAGE_MAP()

void CStatusDlg::AppendLine(const CString& s) {
    // 간단히 타이틀에 누적 출력(실전은 리스트/에디트 컨트롤에 Append 권장)
    CString now; now.Format(L"[Status] %s", s.GetString());
    SetWindowText(now);
}

LRESULT CStatusDlg::OnIoEvent(WPARAM, LPARAM lParam) {
    auto* p = reinterpret_cast<IoEventPayload*>(lParam);
    if (p) {
        CString s; s.Format(L"IOEvent id=%s signal=%s", p->id.GetString(), p->signal.GetString());
        AppendLine(s);
        delete p;
    }
    return 0;
}

LRESULT CStatusDlg::OnMesReply(WPARAM, LPARAM lParam) {
    auto* p = reinterpret_cast<MesReplyPayload*>(lParam);
    if (p) {
        CString s; s.Format(L"MESReply id=%s ok=%d detail=%s",
            p->id.GetString(), p->ok, p->detail.GetString());
        AppendLine(s);
        delete p;
    }
    return 0;
}
