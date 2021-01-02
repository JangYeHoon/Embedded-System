#!/bin/sh
arecord --format=S16_LE --duration=5 --rate=44000 --file-type=wav a.wav
aplay --format=S16_LE --rate=44000 a.wav
rm a.wav
