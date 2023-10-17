#include "baseseekable.h"

BaseSeekable::BaseSeekable()
{

}
class BaseSeekable {
  getSeekSeconds(e) {
    return Mt.warn("Seeking by predetermined amounts are not supported in this playback method"), {BACK: 0, FORWARD: 0};
  }
  seekBackward(e = js) {
    Mt.warn("seekBackward is not supported in this playback method");
  }
  seekForward(e = js) {
    Mt.warn("seekForward is not supported in this playback method");
  }
  seekToTime(e, n) {
    return _asyncToGenerator$t(function* () {
      Mt.warn("seekToTime is not supported in this playback method");
    })();
  }
  constructor(e) {
    this.mediaItemPlayback = e, this.canSeek = false;
  }
}
