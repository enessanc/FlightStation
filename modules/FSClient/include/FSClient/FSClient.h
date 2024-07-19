#pragma once
#include "NL/NL.h"
#include "FGSCommon/FGSCommon.h"
#include "TSML.h"

namespace FS
{
    enum class FSClientExceptions : uint8_t
    {
        NotUsed = 0
    };

    class FSClient final : public TSML::MainNode<CommonMsg, FSClientExceptions>
    {
    public:
        explicit FSClient(TSML::TSMLContext<CommonMsg> *context , std::string node_id = "FSClient");

    protected:
        void OnInitialize() override;
        void OnRun() override;
        void OnMessage(TSML::Message<CommonMsg> msg) override;
        void OnFinish() override;
        void OnException(const TSML::TSMLException<FSClientExceptions>& e) override;

    private:
        NL::ClientInterface<FGS::CommonMsg> client_interface;
        FS::FSClientStatus status;
    };

}



