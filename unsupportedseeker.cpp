#include "unsupportedseeker.h"

UnsupportedSeeker::UnsupportedSeeker()
{

}
class UnsupportedSeeker {
  start() {
    Ct.warn("seeker.start is not supported in this playback method");
  }
  end() {
    Ct.warn("seeker.end is not supported in this playback method");
  }
  seekToTime(e) {
    return Ct.warn("seekToTime is not supported in this playback method"), Promise.resolve();
  }
  constructor() {
    this.ended = false;
  }
}
