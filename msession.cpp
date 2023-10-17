#include "msession.h"

MSession::MSession()
{

}
class MSSession extends KeySession {
  attachMedia(e, n) {
    return this.keySystem = n.keySystem, e.addEventListener("msneedkey", this.boundHandleSessionCreation, false), e.addEventListener("mskeyerror", this.boundDispatchKeyError), e;
  }
  detachMedia(e) {
    e.removeEventListener("msneedkey", this.boundHandleSessionCreation, false), e.removeEventListener("mskeyerror", this.boundDispatchKeyError);
  }
  createSession(e) {
    const {initData: n, target: d} = e;
    if (!d.msKeys) {
      const e = new MSMediaKeys(this.keySystem);
      d.msSetMediaKeys(e);
    }
    const h = d.msKeys.createSession(Qt.MP4, n);
    return h.addEventListener("mskeyerror", this.dispatchKeyError), h.addEventListener("mskeymessage", this.startLicenseSession.bind(this)), h;
  }
  applyDelayedCdmUpdates() {}
  loadKeys(e) {
    return _asyncToGenerator$M(function* () {})();
  }
  clearSessions() {
    return _asyncToGenerator$M(function* () {})();
  }
}
