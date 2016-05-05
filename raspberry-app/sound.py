#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import pyaudio
import wave
import sys

CHUNK = 1024

# Lire un son en fonction de son nom
def play(name):
    wf = wave.open("sounds/" + name + ".wav", "rb")
    p = pyaudio.PyAudio()

    stream = p.open(
        format = p.get_format_from_width(wf.getsampwidth()),
        channels = wf.getnchannels(),
        rate = wf.getframerate(),
        output = True)

    data = wf.readframes(CHUNK)

    while data != "":
        stream.write(data)
        data = wf.readframes(CHUNK)

    stream.stop_stream()
    stream.close()
    p.terminate()


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "SOUND",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
