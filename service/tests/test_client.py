#!/usr/bin/env python3
import asyncio
import websockets
import json
import wave
import argparse

def read_pcm_from_wav(filepath):
    """Read WAV file and extract raw PCM data"""
    with wave.open(filepath, 'rb') as w:
        if w.getnchannels() != 1:
            raise ValueError("Only mono audio supported")
        if w.getsampwidth() != 2:
            raise ValueError("Only 16-bit audio supported")
        pcm_data = w.readframes(w.getnframes())
        return pcm_data

async def test_client():
    parser = argparse.ArgumentParser()
    parser.add_argument('--host', default='192.168.0.155')
    parser.add_argument('--port', type=int, default=10095)
    parser.add_argument('--audio', required=True)
    args = parser.parse_args()
    
    uri = f"ws://{args.host}:{args.port}"
    
    async with websockets.connect(uri) as ws:
        print(f"Connected to {uri}")
        
        # Step 1: Send JSON config
        config = {
            "reqid": "test001",
            "mode": "offline",
            "wav_name": "test.wav",
            "is_speaking": True
        }
        await ws.send(json.dumps(config))
        print(f"Sent config: {config}")
        
        # Step 2: Send raw PCM data (binary) - NOT WAV file
        pcm_data = read_pcm_from_wav(args.audio)
        await ws.send(pcm_data)
        print(f"Sent PCM audio: {len(pcm_data)} bytes")
        
        # Step 3: Send JSON finish signal
        finish = {"is_speaking": False}
        await ws.send(json.dumps(finish))
        print(f"Sent finish: {finish}")
        
        # Receive response
        response = await ws.recv()
        print(f"Response: {response}")

if __name__ == "__main__":
    asyncio.run(test_client())
