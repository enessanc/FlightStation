#include <utility>

#include "VideoStreamer/VideoStreamer.h"

namespace FS
{
    VideoStreamer::VideoStreamer(TSML::TSMLContext<CommonMsg>* context, std::string node_id)
        : TSML::ThreadNode<CommonMsg, VideoStreamerExceptions>(context, std::move(node_id))
    {
        status.video_streamer_state.is_hardware = false;
        status.video_streamer_state.stream_protocol = StreamProtocol::H264;
        status.video_streamer_state.stream_state = StreamState::Closed;
        status.video_streamer_state.model_state = ModelState::TrackEnabled;
    }

    void VideoStreamer::OnInitialize()
    {
        video_capturer.open("/home/andalzo/CLionProjects/FlightStation/data/Serenity.mp4");
        //Note: For webcam or camera connection video_capturer.open(0, cv::CAP_V4L2) worked for me

        if(!video_capturer.isOpened())
        {
            std::cout << "[LOG-ERROR][VideoStreamer]: Video not opened";
        }
        int frame_width = static_cast<int>(video_capturer.get(cv::CAP_PROP_FRAME_WIDTH));
        int frame_height = static_cast<int>(video_capturer.get(cv::CAP_PROP_FRAME_HEIGHT));

        video_writer.open(video_context.h264_software_stream,
                          cv::CAP_GSTREAMER,
                          30,
                          cv::Size(frame_width, frame_height),
                          true);

        status.video_streamer_state.stream_state = StreamState::StreamingAndRecording;
    }

    void VideoStreamer::OnRun()
    {
        if(video_capturer.isOpened())
        {
            cv::Mat frame;
            video_capturer>>frame;
            if(frame.empty())
            {
                std::cout << "[LOG-ERROR][VideoStreamer]: Frame cannot be read";
            }

            frame = OnFrameUpdate(frame);
            video_writer.write(frame);
        }
    }

    void VideoStreamer::OnMessage(TSML::Message<CommonMsg> msg)
    {
        switch (msg.header.id)
        {
            case CommonMsg::SetVideoHandlerState:
            {
                StreamState state;
                msg >> state;
                switch(state)
                {
                    case StreamState::Closed:
                        FinishLoop();
                        break;
                    case StreamState::Streaming:
                        break;
                    case StreamState::StreamingAndRecording:
                        break;
                }
                break;
            }
        }
    }

    void VideoStreamer::OnFinish()
    {
        video_capturer.release();
        video_writer.release();
    }

    void VideoStreamer::OnException(const TSML::TSMLException<VideoStreamerExceptions>& e)
    {

    }

    cv::Mat VideoStreamer::OnFrameUpdate(const cv::Mat& frame)
    {
        //Here video frame will be processed.
        return frame;
    }
}
