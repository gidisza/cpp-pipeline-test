// include the librealsense C++ header file
#include <librealsense2/rs.hpp>
#include<iostream>
// include OpenCV header file
#include <opencv2/opencv.hpp>
#include<vector>
#include<algorithm>
#include<chrono>
using namespace std;
using namespace cv;
using Duration = std::chrono::microseconds;

int main()
{
    //Contruct a pipeline which abstracts the device
    rs2::pipeline pipe;
    cout<<"Hello World\n"<<endl;
    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;

    //Add desired streams to configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

    //Instruct pipeline to start streaming with the requested configuration
    pipe.start(cfg);

    // Camera warmup - dropping several first frames to let auto-exposure stabilize
    rs2::frameset frames;
    std::vector<Duration> times;
    rs2::decimation_filter decimate(1);
    for(int i = 0; i < 30; i++)
    {
        //Wait for all configured streams to produce a frame
        auto start = std::chrono::high_resolution_clock::now();

        frames = pipe.wait_for_frames();
        rs2::depth_frame depth = frames.get_depth_frame();
        depth = decimate.process(depth);
        auto elapsed = std::chrono::duration_cast<Duration>( std::chrono::high_resolution_clock::now() - start);
        times.push_back(elapsed);

    }
   
    for (auto time : times)
    {
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
       cout<<microseconds<<endl;
    }
    
    //Get each frame
    rs2::frame color_frame = frames.get_color_frame();

    // Creating OpenCV Matrix from a color image
    Mat color(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);

    // Display in a GUI
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", color);

    waitKey(0);

    return 0;
}