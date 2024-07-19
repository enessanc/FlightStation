#include <iostream>
#include "FSClient/FSClient.h"
#include "VideoStreamer/VideoStreamer.h"

int main() {
    std::cout << "[FESA]: Hello, World!" << std::endl;

    TSML::TSMLContext<FS::CommonMsg> context;
    FS::FSClient fs_client(&context);
    fs_client.InitializeLoop();

    FS::VideoStreamer video_streamer(&context);
    video_streamer.InitializeLoop();

    video_streamer.StartLoop();

    fs_client.StartLoop();

    if(video_streamer.IsJoinable())
    {
        video_streamer.Join();
    }

    return 0;
}
