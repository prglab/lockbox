/**
	Demo app for FileWatcher. FileWatcher is a simple wrapper for the file
	modification system in Windows and Linux.

	@author James Wynn
	@date 2/25/2009

	Copyright (c) 2009 James Wynn (james@jameswynn.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

#include <file_watcher.h>
#include <iostream>
#include <cstdlib>

/// Processes a file action
class UpdateListener : public FW::FileWatchListener {
public:
	UpdateListener() {}
	void handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename,
		FW::Action action) {
		std::cout << "DIR (" << dir + ") FILE (" + filename + ") has event " << action << std::endl;
	}
};


int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Check code." << std::endl;
    exit(1);
  }

  std::string watch_dir(argv[1]);

	try {
		// create the file watcher object
		FW::FileWatcher fileWatcher;

		// add a watch to the system
		FW::WatchID watchID = fileWatcher.addWatch(watch_dir, new UpdateListener(), true);

		std::cout << "Press ^C to exit demo" << std::endl;

		// loop until a key is pressed
		while(1) {
			fileWatcher.update();
		}
	} catch( std::exception& e ) {
    std::cerr << "An exception has occurred: " << e.what() << std::endl;
	}

	return 0;
}
