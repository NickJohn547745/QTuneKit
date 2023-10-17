#include "trackpersistence.h"

TrackPersistence::TrackPersistence()
{

}
class TrackPersistence {
  getPersistedTrack() {
    var e;
    if (!hasLocalStorage()) return false;
    const n = (null === (e = getLocalStorage()) || void 0 === e ? void 0 : e.getItem(this.storageKey)) || "";
    try {
      return JSON.parse(n);
    } catch (Mr) {
      return Ct.warn("MEDIA_TRACK could not parse persisted value " + n), false;
    }
  }
  setPersistedTrack(e) {
    var n, d;
    if (!hasLocalStorage()) return;
    if (Ct.debug(`MEDIA_TRACK setPersistedTrack ${e.language},${e.label},${e.kind} with keys ${this.fields}`), !e) return void (null === (d = getLocalStorage()) || void 0 === d || d.setItem(this.storageKey, ""));
    const h = JSON.stringify(this.extractFieldValuesFromTrack(e));
    Ct.debug("MEDIA_TRACK Extracted values " + h), null === (n = getLocalStorage()) || void 0 === n || n.setItem(this.storageKey, h);
  }
  extractFieldValuesFromTrack(e) {
    const n = {};
    return this.fields.forEach(d => {
      const h = e[d];
      null == h && Ct.warn(`MEDIA_TRACK No value for field ${d} on track ${JSON.stringify(e)}`), n[d] = h;
    }), n;
  }
  constructor(e, n) {
    this.storageKey = e, this.fields = n;
  }
}
