ffmpeg -framerate  5 -i video/video%02d.png -c:v libx264 -r 30 -pix_fmt yuv420p video1.mp4
ffmpeg -framerate 25 -i video/video%02d.png -c:v libx264 -r 30 -pix_fmt yuv420p video2.mp4
