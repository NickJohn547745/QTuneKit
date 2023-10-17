#include "capabilities.h"

Capabilities::Capabilities()
{

}
class Capabilities {
  set controller (e) {
    this._mediaSession.controller = e;
  }
  updateChecker(e) {
    this._checkCapability !== e && (this._checkCapability = e, this._dispatcher.publish(ss.capabilitiesChanged));
  }
  get canEditPlaybackQueue() {
    return this._checkCapability(Ss.EDIT_QUEUE);
  }
  get canPause() {
    return this._checkCapability(Ss.PAUSE);
  }
  get canSeek() {
    return this._checkCapability(Ss.SEEK);
  }
  get canSetRepeatMode() {
    return this._checkCapability(Ss.REPEAT);
  }
  get canSetShuffleMode() {
    return this._checkCapability(Ss.SHUFFLE);
  }
  get canSkipToNextItem() {
    return this._checkCapability(Ss.SKIP_NEXT);
  }
  get canSkipToMediaItem() {
    return this._checkCapability(Ss.SKIP_TO_ITEM);
  }
  get canSkipToPreviousItem() {
    return this._checkCapability(Ss.SKIP_PREVIOUS);
  }
  get canAutoplay() {
    return this._checkCapability(Ss.AUTOPLAY);
  }
  get canSetVolume() {
    return this._checkCapability(Ss.VOLUME);
  }
  constructor(e) {
    this._dispatcher = e, this._checkCapability = e => e === Ss.VOLUME, this._mediaSession = new MediaSessionManager(this, e);
  }
}
