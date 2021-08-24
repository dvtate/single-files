#!/bin/sh
VIDEO=layer01.mp4
LEN=$(ffprobe -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1 "$VIDEO")
CHUNKSIZE=30
EPSILON=0.1
CHUNKS=4 # $(echo "scale=0;($LEN + $CHUNKSIZE - $EPSILON) / $CHUNKSIZE" | bc)
for C in $(seq 0 $(($CHUNKS-1))); do
    # add echo to the front to see output as test
    ffmpeg -ss $(printf "%02i" $(( $C * $CHUNKSIZE / 3600 ))):$(printf "%02i" $(( $C * $CHUNKSIZE / 60 % 60 ))):$(printf "%02i" $(( $C * $CHUNKSIZE % 60))) -i "$VIDEO" -t $CHUNKSIZE -sn -c:a aac -b:a 256k -pix_fmt yuv420p -c:v libx264 -crf 14 fleets/$(($C+1)).mp4
done
