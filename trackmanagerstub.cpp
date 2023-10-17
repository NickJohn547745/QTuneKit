#include "trackmanagerstub.h"

TrackManagerStub::TrackManagerStub()
{

}
class TrackManagerStub {
  get isDestroyed() {
    return this._isDestroyed;
  }
  get currentTrack() {
    return {};
  }
  set currentTrack (e) {}
  get tracks() {
    return [];
  }
  destroy() {
    this._isDestroyed = true;
  }
  restoreSelectedTrack() {}
  constructor() {
    this._isDestroyed = false;
  }
}
