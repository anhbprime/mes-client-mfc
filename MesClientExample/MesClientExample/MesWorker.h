// MesWorker.h
#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include "MesMessages.h"

class MesWorker
{
public:
    MesWorker() = default;

    void SetOwner(HWND hOwner) { m_hOwner = hOwner; }

    void SimulateRecipeReply()
    {
        if (m_hOwner == nullptr)
            return;

        static int s_version = 1;
        std::string recipeName = "RCP_FROM_WORKER";
        int version = s_version++;

        auto msg = std::make_unique<MesRecipeDownloadMsg>(recipeName, version);
        MesOpCode op = msg->OpCode();

        ::PostMessage(
            m_hOwner,
            WM_MES_REPLY,
            static_cast<WPARAM>(op),
            reinterpret_cast<LPARAM>(msg.release())   // 소유권 UI(MainFrm→Dlg)로 이동
        );
    }

private:
    HWND m_hOwner{ nullptr };   // 보통 MainFrm HWND
};
