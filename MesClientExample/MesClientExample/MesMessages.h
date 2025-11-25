// MesMessages.h
#pragma once
#include <Windows.h>
#include <string>

constexpr UINT WM_MES_REPLY = WM_APP + 1;

enum class MesOpCode : UINT
{
    Unknown = 0,
    RecipeDownload = 1,
    Alarm = 2,
};

class MesBase
{
public:
    explicit MesBase(MesOpCode op) : m_op(op) {}
    virtual ~MesBase() = default;

    MesOpCode OpCode() const { return m_op; }

private:
    MesOpCode m_op;
};

class MesRecipeDownloadMsg : public MesBase
{
public:
    MesRecipeDownloadMsg(std::string recipeName, int version)
        : MesBase(MesOpCode::RecipeDownload)
        , m_recipeName(std::move(recipeName))
        , m_version(version)
    {
    }

    const std::string& RecipeName() const { return m_recipeName; }
    int Version() const { return m_version; }

private:
    std::string m_recipeName;
    int m_version;
};
