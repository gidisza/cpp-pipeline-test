import datetime
import pyrealsense2 as rs
import numpy as np
import cv2
import time

@profile
def grab_frame(pipeline,rs_frames_align_object,decimate):
    frames = pipeline.wait_for_frames()
    time.sleep(0.01)
    aligned_frames = rs_frames_align_object.process(frames)
    
    depth_frame = aligned_frames.get_depth_frame()
    color_frame = aligned_frames.get_color_frame()
    depth_frame = decimate.process(depth_frame)

@profile
def main():
    pipeline = rs.pipeline()
    config = rs.config()
    config.enable_stream(rs.stream.depth, rs.format.z16, 30)
    config.enable_stream(rs.stream.color, rs.format.bgr8, 30)  # rgb8
    times = []
    pipeline.start(config)
    frames = pipeline.wait_for_frames()

    decimate = rs.decimation_filter()
    rs_frames_align_object = rs.align(rs.stream.color)
    decimate.set_option(rs.option.filter_magnitude, 1)
    for i in range(100):
        a = datetime.datetime.now()
        grab_frame(pipeline=pipeline,decimate=decimate,rs_frames_align_object=rs_frames_align_object)
        b = datetime.datetime.now()
        c = b - a
        times.append(c.total_seconds())
    for time in times:
        print(time)
    print(sum(times)/len(times))
if __name__ == "__main__":
    main()