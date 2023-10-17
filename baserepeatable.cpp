#include "baserepeatable.h"

BaseRepeatable::BaseRepeatable()
{

}
class BaseRepeatable {
  get repeatMode() {
    return e.PlayerRepeatMode.none;
  }
  set repeatMode (e) {
    e !== this.repeatMode && Mt.warn("setting repeatMode is not supported in this playback method");
  }
  constructor() {
    this.canSetRepeatMode = false;
  }
}
