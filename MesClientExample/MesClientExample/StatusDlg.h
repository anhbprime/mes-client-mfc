#pragma once
#include <afxdialogex.h>
#include "Messages.h"
#include "resource.h"
class CStatusDlg : public CDialogEx {
    DECLARE_DYNAMIC(CStatusDlg)
public:
    CStatusDlg(CWnd* pParent = nullptr);
    virtual ~CStatusDlg();

    enum { IDD = IDD_STATUSDLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX) override;
    DECLARE_MESSAGE_MAP()

public:
    // 사용자 메시지 핸들러
    afx_msg LRESULT OnIoEvent(WPARAM, LPARAM);
    afx_msg LRESULT OnMesReply(WPARAM, LPARAM);

private:
    void AppendLine(const CString& s);
public:
    CListBox list1;
};