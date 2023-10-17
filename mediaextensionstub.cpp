#include "mediaextensionstub.h"

MediaExtensionStub::MediaExtensionStub()
{

}
class MediaExtensionStub extends Notifications {
  destroy(e) {}
  setMediaItem(e) {}
  initializeKeySystem() {
    var e = this;
    return _asyncToGenerator$D(function* () {
      e.session = new EncryptedSession;
    })();
  }
  clearSessions() {
    return _asyncToGenerator$D(function* () {})();
  }
  constructor(e) {
    super(e), this.audioTracks = [], this.textTracks = [], this.extURI = "", this.hasMediaKeySupport = true, this.initiated = true, this.isFairplay = true, this.hasMediaKeySupport = true, this.hasMediaSession = true;
  }
}
