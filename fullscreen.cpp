#include "fullscreen.h"

Fullscreen::Fullscreen()
{

}
class Fullscreen {
  exit() {
    var e = this;
    return _asyncToGenerator$V(function* () {
      if (e.isInFullscreen()) return e.stopDispatchingEvents(() => e.exitFullscreen());
    })();
  }
  request(e) {
    var n = this;
    return _asyncToGenerator$V(function* () {
      if (void 0 !== e) return n.stopDispatchingEvents(() => n.requestFullscreenForElement(e));
    })();
  }
  stopDispatchingEvents(e) {
    var n = this;
    return _asyncToGenerator$V(function* () {
      return n.player.windowHandlers.stopListeningToVisibilityChanges(e);
    })();
  }
  exitFullscreen() {
    return ti();
  }
  isInFullscreen() {
    return ri();
  }
  requestFullscreenForElement(e) {
    return ni(e);
  }
  constructor(e) {
    this.player = e;
  }
}
