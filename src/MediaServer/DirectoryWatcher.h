#pragma once

#include "ofMain.h"
#include "SourceType.h"

namespace ofx {
namespace piMapper {

class DirectoryWatcher : public ofThread {
	public:
		DirectoryWatcher(std::string path, int watcherMediaType);
		virtual ~DirectoryWatcher();
		std::vector<std::string> &getFilePaths();
		int getMediaType();

		void beginWatch(int intervalInMillis = 5000);
		void threadedFunction();

		/**
 		 * Notifies when files are added to this directory.
		 * Sender is a pointer to this DirectoryWatcher
		 */
		ofEvent<void> directoryFileAddedEvent;
		/**
 		 * Notifies when files are removed from this directory.
		 * Sender is a pointer to this DirectoryWatcher
 		*/
		ofEvent<void> directoryFileRemovedEvent;

	private:
		ofDirectory _directory;
		std::vector<std::string> _filePaths;
		std::string directoryPath;
		int _mediaType;

		int dirSize;
		long watchInterval; // in millis.
};

} // namespace piMapper
} // namespace ofx
