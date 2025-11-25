#pragma once
#include <afxwin.h>
#include <thread>
#include <atomic>
#include <chrono>
#include "Messages.h"

class CIOWorker {
public:
    explicit CIOWorker(HWND hNotify) : m_hNotify(hNotify) {}
    ~CIOWorker() { stop(); }

    void start() {
        if (m_running.exchange(TRUE)) return;
        m_th = std::jthread([this](std::stop_token st) { loop(st); });
    }

    void stop() {
        if (!m_running.exchange(FALSE)) return;
        if (m_th.joinable()) m_th.request_stop(), m_th.join();
    }

private:
    void loop(std::stop_token st) {
        using namespace std::chrono_literals;
        int seq = 0;
        while (!st.stop_requested()) {
            std::this_thread::sleep_for(1500ms);
            TRACE(L"[IoEventWorker] tick\n");
            
            // 가상 이벤트 생성
            auto* p = new IoEventPayload;
            p->id.Format(L"EVT-%04d", ++seq);
            p->signal = (seq % 2) ? L"LOAD" : L"UNLOAD";

            ::PostMessage(m_hNotify, WM_IO_EVENT, 0, reinterpret_cast<LPARAM>(p));
        }
    }

    HWND m_hNotify = nullptr;
    std::jthread m_th;
    std::atomic<BOOL> m_running{ FALSE };
};
