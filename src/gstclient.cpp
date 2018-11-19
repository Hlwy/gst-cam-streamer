#include <iostream>
#include <glib.h>
#include <gst/gst.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, char *argv[]){
     std::cout << cv::getBuildInformation() << std::endl;

     // // Working Pipeline
     // VideoCapture cap("udpsrc port=5000 ! application/x-rtp, media=(string)video, clock-rate=(int)90000 ! rtph264depay ! avdec_h264 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");

     // Experimental Pipeline
     VideoCapture cap("udpsrc port=5000 ! application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! h264parse ! queue ! avdec_h264 ! videoconvert ! appsink sync=false async=false", CAP_GSTREAMER);

     if(!cap.isOpened()){
          std::cout<<"VideoCapture not opened"<<std::endl;
          exit(-1);
     }

     Mat frame;

     while(true){

          cap.read(frame);

          if(frame.empty())
               break;
          // cvtColor(frame, frame, CV_BGR_I4202BGR);

          imshow("Client", frame);
          if(waitKey(1) == 's')
               break;
     }

     destroyWindow("Client");

     // GstElement *pipeline, *videosrc, *que, *parse, *conv,*enc, *pay, *udp;
     // GMainLoop *loop;
     //
     // // init GStreamer
     // gst_init(&argc, &argv);
     // loop = g_main_loop_new(NULL, FALSE);
     //
     // // setup pipeline
     // pipeline = gst_pipeline_new("pipeline");
     // videosrc = gst_element_factory_make("autovideosrc", "source");
     // conv = gst_element_factory_make("videoconvert", "conv");
     // que = gst_element_factory_make("queue", "que");
     // parse = gst_element_factory_make("h264parse", "parse");
     //
     // enc = gst_element_factory_make("x264enc", "enc");
     // g_object_set(G_OBJECT(enc), "bitrate", 1024, NULL);
     // g_object_set(G_OBJECT(enc), "speed-preset", 2, NULL);
     // g_object_set(G_OBJECT(enc), "qp-min", 30, NULL);
     // g_object_set(G_OBJECT(enc), "threads", 4, NULL);
     // g_object_set(G_OBJECT(enc), "tune", 0x4, NULL);
     //
     // pay = gst_element_factory_make("rtph264pay", "pay");
     // g_object_set(G_OBJECT(pay), "config-interval", 1, NULL);
     // g_object_set(G_OBJECT(pay), "pt", 96, NULL);
     //
     // udp = gst_element_factory_make("udpsink", "udp");
     // g_object_set(G_OBJECT(udp), "host", "192.168.2.52", NULL);
     // g_object_set(G_OBJECT(udp), "port", 5000, NULL);
     //
     // gst_bin_add_many(GST_BIN (pipeline), videosrc, conv, enc, parse, que, pay, udp, NULL);
     //
     // if(gst_element_link_many(videosrc, conv, enc, pay, udp, NULL) != TRUE){
     //      return -1;
     // }
     //
     // // play
     // gst_element_set_state(pipeline, GST_STATE_PLAYING);
     //
     // g_main_loop_run(loop);
     //
     // // clean up
     // gst_element_set_state(pipeline, GST_STATE_NULL);
     // gst_object_unref(GST_OBJECT (pipeline));
     // g_main_loop_unref(loop);
     //

     return 0;
}
