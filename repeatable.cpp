#include "repeatable.h"

Repeatable::Repeatable()
{

}
class Repeatable {
  get repeatMode() {
    return this._repeatMode;
  }
  set repeatMode (n) {
    n in e.PlayerRepeatMode && n !== this._repeatMode && (this._repeatMode = n, this.dispatcher.publish(ss.repeatModeDidChange, this._repeatMode));
  }
  constructor(n, d = e.PlayerRepeatMode.none) {
    this.canSetRepeatMode = true, this.dispatcher = n, this._repeatMode = d;
  }
}
