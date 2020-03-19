#pragma once

#include "ofMain.h"
#include "DirectoryWatcher.h"

#include "BaseSource.h"
#include "ImageSource.h"
#include "VideoSource.h"
#include "FboSource.h"
#include "SourceType.h"

#define DEFAULT_IMAGES_DIR "sources/images/"
#define DEFAULT_VIDEOS_DIR "sources/videos/"

#define PI_IMAGES_DIR "/boot/ofxpimapper/sources/images/"
#define PI_VIDEOS_DIR "/boot/ofxpimapper/sources/videos/"

/* 
 * These you can get when you apt-get install usbmount
 */
#define USB0_IMAGES_DIR "/media/usb0/"
#define USB1_IMAGES_DIR "/media/usb1/"
#define USB2_IMAGES_DIR "/media/usb2/"
#define USB3_IMAGES_DIR "/media/usb3/"

#define USB0_VIDEOS_DIR "/media/usb0/"
#define USB1_VIDEOS_DIR "/media/usb1/"
#define USB2_VIDEOS_DIR "/media/usb2/"
#define USB3_VIDEOS_DIR "/media/usb3/"

// TODO: Change this into a externally configurable list

/*

Considering that the pi has 4 USB ports, there is a possibility to connect 4 USB flash drives. The paths to them would be 
	/media/usb0
	/media/usb1
	/media/usb2
	/media/usb3
We need all of them and we search for mp4, jpg and png files there.

*/

namespace ofx {
namespace piMapper {

class MediaServer {
	public:
		MediaServer();
	
		void setup();
		void update();
		void draw();

		int getNumVideos();
		int getNumImages();
		int getNumFboSources(); // new
		std::vector<std::string> & getVideoPaths();
		std::vector<std::string>  getVideoNames();
		std::vector<std::string> & getImagePaths();
		std::vector<std::string>  getImageNames();
		std::vector<std::string>  getFboSourceNames(); // new

		BaseSource * loadMedia(std::string & path, int mediaType);
		BaseSource * loadImage(std::string & path);
		void unloadImage(std::string & path);
		BaseSource * loadVideo(std::string & path);
		void unloadVideo(std::string & path);
		void unloadMedia(std::string & path);
		void clear(); // Force all loaded source unload
		BaseSource * getSourceByPath(std::string & mediaPath);
		std::string getDefaultImageDir();
		std::string getDefaultVideoDir();
		std::string getDefaultMediaDir(int sourceType);

		// Do things with FBO sources
		void addFboSource(FboSource & fboSource); // could be called also as register FBO source
		void addFboSource(FboSource * fboSource);
	
		BaseSource * loadFboSource(std::string & fboSourceName);
		void unloadFboSource(std::string & fboSourceName);

		// Custom events, add/remove
		ofEvent <std::string> onImageAdded;
		ofEvent <std::string> onImageRemoved;
		ofEvent <std::string> onVideoAdded;
		ofEvent <std::string> onVideoRemoved;
		ofEvent <std::string> onFboSourceAdded;
		ofEvent <std::string> onFboSourceRemoved;
		// load/unload
		ofEvent <std::string> onImageLoaded;
		ofEvent <std::string> onImageUnloaded;
		ofEvent <std::string> onVideoLoaded;
		ofEvent <std::string> onVideoUnloaded;
		ofEvent <std::string> onFboSourceLoaded;
		ofEvent <std::string> onFboSourceUnloaded;

	private:
		// Directory Watchers
		DirectoryWatcher videoWatcher;
		DirectoryWatcher piVideoWatcher;
		DirectoryWatcher usb0VideoWatcher;
		DirectoryWatcher usb1VideoWatcher;
		DirectoryWatcher usb2VideoWatcher;
		DirectoryWatcher usb3VideoWatcher;
	
		DirectoryWatcher imageWatcher;
        DirectoryWatcher piImageWatcher;
		DirectoryWatcher usb0ImageWatcher;
		DirectoryWatcher usb1ImageWatcher;
		DirectoryWatcher usb2ImageWatcher;
		DirectoryWatcher usb3ImageWatcher;
	
        std::vector<std::string> _tempImagePaths;
        std::vector<std::string> _tempVideoPaths;
    
		map <std::string, BaseSource *> loadedSources;
	
		// FBO source storage before they go to loadedSources
		std::vector<FboSource *> fboSources; // FBO source storage
};

} // namespace piMapper
} // namespace ofx
