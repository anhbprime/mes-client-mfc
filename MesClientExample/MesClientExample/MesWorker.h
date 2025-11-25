// MesWorker.h
#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include "MesMessages.h"

class MesWorker
{
public:
    MesWorker() = default;
    ~MesWorker()
    {
        Stop(); 
    }

    void SetOwner(HWND hOwner) { m_hOwner = hOwner; }

    void Start()
    {
        if (m_thread.joinable())
            return; 

        m_thread = std::jthread(
            [this](std::stop_token st)
            {
                this->Loop(st);
            }
        );
    }

    // 워커 스레드 정지
    void Stop()
    {
        if (m_thread.joinable())
        {
            m_thread.request_stop();
        }
    }

private:
    void Loop(std::stop_token st)
    {
        using namespace std::chrono_literals;
        int seq = 0;

        while (!st.stop_requested())
        {
            std::this_thread::sleep_for(1000ms);
            TRACE(L"[MesWorker] tick\n");

            HWND hOwner = m_hOwner;
            if (!hOwner || !::IsWindow(hOwner))
                continue;

            std::string recipeName = "RCP_FROM_WORKER";
            int version = ++seq;

            auto msg = std::make_unique<MesRecipeDownloadMsg>(recipeName, version);
            MesOpCode op = msg->OpCode();

            ::PostMessage(
                hOwner,
                WM_MES_REPLY,
                static_cast<WPARAM>(op),
                reinterpret_cast<LPARAM>(msg.release())
            );
        }
    }

private:
    HWND       m_hOwner{ nullptr }; 
    std::jthread m_thread;     
};
