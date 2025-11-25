#pragma once
#include <afxwin.h>

constexpr UINT WM_IO_EVENT = WM_APP + 1;

struct IoEventPayload {
    CString id;
    CString signal; // "LOAD"/"UNLOAD"
};

struct MesReplyPayload {
    CString id;
    BOOL    ok;
    CString detail;
};
