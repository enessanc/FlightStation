#include <utility>

#include "FSClient/FSClient.h"

namespace FS
{
    FSClient::FSClient(TSML::TSMLContext<CommonMsg>* context, std::string node_id) :
        TSML::MainNode<FS::CommonMsg, FS::FSClientExceptions>(context, std::move(node_id))
    {

    }

    void FSClient::OnInitialize()
    {
        do
        {
            client_interface.Connect("127.0.0.1",18500);
        }  while(!client_interface.IsConnected());

        if(client_interface.IsConnected())
        {
            status.state = FSClientState::Connected;
            std::cout << "[LOG-DEBUG][FSClient]: Connected." << std::endl;
        }

    }

    void FSClient::OnRun()
    {
        if (client_interface.IsConnected())
        {
            while(!client_interface.InComing().empty())
            {
                NL::Message<FGS::CommonMsg> inc_msg = client_interface.InComing().pop_front().msg;
                switch(inc_msg.header.id)
                {
                case FGS::CommonMsg::FSValidated:
                    status.state = FSClientState::Validated;
                    std::cout << "[LOG-DEBUG][FSClient]: Validated." << std::endl;
                    break;
                case FGS::CommonMsg::SetFSState:
                    break;
                case FGS::CommonMsg::FSStatus:
                    break;
                default:
                    break;
                }
            }
            // TODO: Send FS status here with maximum 10 Hz frequency.

            NL::Message<FGS::CommonMsg> fs_status_message;
            fs_status_message.header.id = FGS::CommonMsg::FSStatus;
            fs_status_message << CommonMsg::VideoHandlerStatus;
            //Add video handler status struct.
            fs_status_message << CommonMsg::PX4ControllerStatus;
            //Add px4 controller status struct

            client_interface.Send(fs_status_message);
        }
        else
        {
            FinishLoop();
        }
    }

    void FSClient::OnMessage(TSML::Message<CommonMsg> msg)
    {
        switch (msg.header.id)
        {
        case CommonMsg::PX4ControllerStatus:
            break;
        case CommonMsg::VideoHandlerStatus:
            break;
        default:
            break;
        }
    }

    void FSClient::OnFinish()
    {
        client_interface.Disconnect();
        TSML::Message<CommonMsg> msg;
        msg.header.id = CommonMsg::SetVideoHandlerState;
        StreamState state = StreamState::Closed;
        msg << state;
        Send("VideoStreamer", msg);
    }

    void FSClient::OnException(const TSML::TSMLException<FSClientExceptions>& e)
    {

    }
}


