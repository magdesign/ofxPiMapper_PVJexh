# Remote Control Client for ofxPiMapper

This example demonstrates a TCP **client** for ofxPiMapper remote control. The other part of this is the [Remote Control Server](../example_remote-server). What it does is the following.

- Reads IP address and port defined in `bin/data/config.json`.
- Connects to server by using the IP address and port.
- Once connected, ofxPiMapper configuration is received.
- Instance of ofxPiMapper class is being set up.
- TCP messages are sent on every keyboard and mouse event.

In reality this example should be used as the remote control residing on your laptop computa. Set up your Raspberry Pi, connect it to the same network as your laptop and get to know the IP address of the Raspberry Pi. Update `bin/data/config.json` with the IP address of your Raspberry Pi and launch the app!

**Warning!** Sources are not being sent. Click once with the mouse after the application launches to see the borders of the surfaces. There should be a green rectangle visible in the top left corner of the screen if the connection is successfull.

## Dependencies

JSON is used as the data format between ofxPiMapper remote control server and client, therefore additionally [ofxJSON](https://github.com/jeffcrouse/ofxJSON) addon is used. Install it by using the following lines of bash code.

```
cd openFrameworks/addons
git clone --depth=1 https://github.com/jeffcrouse/ofxJSON
```
